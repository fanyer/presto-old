# -*- tab-width: 4; indent-tabs-mode: t; -*-

import sys
import os
import re
import glob
import string

in_shaders_enum = os.path.join("modules", "libvega", "vega3ddevice.h")

in_opengl_backend = os.path.join("platforms", "vega_backends", "opengl")
in_shaders_glsl = os.path.join(in_opengl_backend, "shaders")
in_shaders_glsl_index = os.path.join(in_shaders_glsl, "index.txt")

out_shaderdata_glsl = os.path.join(in_opengl_backend, "vegagldevice_shaderdata.cpp")

if not os.path.isdir("modules"):
    os.chdir(os.path.dirname(sys.argv[0]))
    while not os.path.isdir("modules"):
        prevdir = os.getcwd()
        os.chdir("..")
        if prevdir == os.getcwd():
            break

shader_list = []

output_paths = False
if len(sys.argv) > 1 and sys.argv[1] == "-pathlist": output_paths = True

# Build shader list from enumeration
def ParseShaderList():
    global shader_list
    global in_shaders_enum

    try:
        shader_enum_h = open(in_shaders_enum, "rt")
    except:
        sys.exit("Can't open 3d-device header (" + in_shaders_enum + ")");

    in_enumeration = False

    for line in shader_enum_h:
        line = line.strip()

        if not in_enumeration:
            if line == "enum ShaderType":
                in_enumeration = True
                continue
        else:
            if line == "};":
                break

            match = re.search("^\s*(SHADER_[_A-Z0-9]+).*", line)
            if match:
                shader_list.append(match.group(1))

    shader_enum_h.close()

    if len(shader_list) == 0:
        sys.exit("Failed to parse shader enumeration, or it was empty.");


# Read (enum => shader-file) index
def ReadShaderIndex(index_file):
    try:
        shader_idx = open(index_file, "rt")
    except:
        sys.exit("Can't open index file " + index_file);

    shader_map = {}

    for line in shader_idx:
        line = line.strip()

        if not line: continue

        if line.startswith("#"): continue

        match = re.search("([_a-zA-Z0-9]+):\s*(\S+)", line)
        if match:
            enum = match.group(1)
            filename = match.group(2)
        
            if enum in shader_map:
                sys.stderr.write("Duplicate definition of " + enum + ". Skipping.\n")
            else:
                shader_map[enum] = filename

    shader_idx.close()

    return shader_map


# Write output
def WriteShaderData(name, shaders, in_path, out_file):
    global shader_list
    global output_paths

    shaderdata = open(out_file, "w")

    print >>shaderdata, "/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-"
    print >>shaderdata, " *"
    print >>shaderdata, " * Copyright (C) 1995-2009 Opera Software AS.  All rights reserved."
    print >>shaderdata, " *"
    print >>shaderdata, " * This file is part of the Opera web browser.  It may not be distributed"
    print >>shaderdata, " * under any circumstances."
    print >>shaderdata, " *"
    print >>shaderdata, " * THIS FILE IS AUTOMATICALLY GENERATED - DO NOT EDIT!"
    print >>shaderdata, " *"
    print >>shaderdata, " */"
    print >>shaderdata
    print >>shaderdata, "#include \"core/pch_system_includes.h\""
    print >>shaderdata
    print >>shaderdata, "#ifdef VEGA_BACKEND_OPENGL"
    print >>shaderdata, "#define VEGA_OPENGL_SHADERDATA_DEFINED"
    print >>shaderdata

    print >>shaderdata, "const char* g_" + name + "_ShaderData[] = {"

    stringdata_arr = []

    def FormatSource(source):
        # Remove single line comments
        source = re.sub("//.*\n", "\n", source)

        # Remove multiline comments
        multiline_com_pat = re.compile(r'/\*.*?\*/', re.DOTALL)
        source = multiline_com_pat.sub("", source)

        # Remove empty lines
        empty_line_pat = re.compile("^[ \t\r\f\v]*\n", re.MULTILINE)
        source = empty_line_pat.sub("", source)

        # Line ending fixes
        source = re.sub(r'\r\n', '\n', source)

        # Whitespace compaction
        source = re.sub(r'[ \t\r\f\v]{2,}', ' ', source)

        return source

    for enum in shader_list:

        if enum not in shaders:
            print "Writing null shader for " + enum
            stringdata_arr.append("\t// " + enum + "\n\tNULL")
            continue

        fn = os.path.join(in_path, shaders[enum]);

        print "Adding shader[" + enum + "] => " + fn

        if output_paths:
            stringdata_arr.append("\t// " + enum + "\n\t\"" +
                                  os.path.join(os.getcwd(), fn).encode('string_escape') + "\"")
        else:
            try:
                f = open(fn, "rb")

                contents = FormatSource(f.read())

                fn_lines = ["\t// " + enum]

                content_lines = contents.split("\n")
                for line in content_lines:
                    if not line: continue
                    fn_lines.append("\t\"" + line.encode('string_escape') + "\\n\"")

                stringdata_arr.append(string.join(fn_lines, "\n"))
                f.close()

            except:
                sys.stderr.write("error processing file: " + fn + "\n")

    fn = os.path.join(in_path, "vert2d.shd");

    print "Adding shader vert2d.shd => " + fn

    if output_paths:
        stringdata_arr.append("\t// vert2d.shd\n\t\"" +
                              os.path.join(os.getcwd(), fn).encode('string_escape') + "\"")
    else:
        try:
            f = open(fn, "rb")

            contents = FormatSource(f.read())

            fn_lines = ["\t// vert2d.shd"]

            content_lines = contents.split("\n")
            for line in content_lines:
                if not line: continue
                fn_lines.append("\t\"" + line.encode('string_escape') + "\"")

            stringdata_arr.append(string.join(fn_lines, "\n"))
            f.close()

        except:
            sys.stderr.write("error processing file: " + fn + "\n")

    print >>shaderdata, string.join(stringdata_arr, ",\n\n")
    print >>shaderdata, "};"
    print >>shaderdata
    print >>shaderdata, "#endif // VEGA_BACKEND_OPENGL"

    shaderdata.close()


ParseShaderList()

shaders = ReadShaderIndex(in_shaders_glsl_index)

if len(shaders) == 0:
    sys.exit("Empty index " + in_shaders_glsl_index);

WriteShaderData("GLSL", shaders, in_shaders_glsl, out_shaderdata_glsl)
