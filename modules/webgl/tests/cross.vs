attribute vec3 position;
attribute vec3 normal;
attribute vec4 UV;
attribute vec4 joints1;
attribute float joints2;
attribute vec4 weights1;
attribute float weights2;
attribute vec3 tangent;
uniform mat4 worldView;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 worldInverseTranspose;
uniform mat4 envMat;
uniform vec3 lightpos0;
uniform vec3 lightdir0;
uniform mat4 lightmat0;
varying vec4 spotcoord0;
varying vec3 eyevec;
varying vec3 lightvec0;
varying vec3 tlightvec0;
varying float lightdist0;
uniform mat4 jointMat[59];
uniform mat4 jointNMat[59];
uniform mat4 layer0Matrix;
varying vec3 textureCoords0;
varying vec3 n;
varying vec3 b;
varying vec3 t;
varying vec4 UVCoord;
varying vec3 OBJCoord;
varying vec3 tang;
varying vec3 teyevec;
void main(void)
{
UVCoord=UV;
OBJCoord = position;
vec4 pos = vec4(0.0, 0.0, 0.0, 1.0);
vec4 norm = vec4(0.0, 0.0, 0.0, 1.0);
vec4 tang4 = vec4(0.0, 0.0, 0.0, 1.0);
pos += jointMat[int(joints1[0])]*vec4(position,1.0)*weights1[0];
norm += jointNMat[int(joints1[0])]*vec4(normal,1.0)*weights1[0];
tang4 +=  jointNMat[int(joints1[0])]*vec4(tangent,1.0)*weights1[0];
pos += jointMat[int(joints1[1])]*vec4(position,1.0)*weights1[1];
norm += jointNMat[int(joints1[1])]*vec4(normal,1.0)*weights1[1];
tang4 +=  jointNMat[int(joints1[1])]*vec4(tangent,1.0)*weights1[1];
pos += jointMat[int(joints1[2])]*vec4(position,1.0)*weights1[2];
norm += jointNMat[int(joints1[2])]*vec4(normal,1.0)*weights1[2];
tang4 +=  jointNMat[int(joints1[2])]*vec4(tangent,1.0)*weights1[2];
pos += jointMat[int(joints1[3])]*vec4(position,1.0)*weights1[3];
norm += jointNMat[int(joints1[3])]*vec4(normal,1.0)*weights1[3];
tang4 +=  jointNMat[int(joints1[3])]*vec4(tangent,1.0)*weights1[3];
pos += jointMat[int(joints2)]*vec4(position,1.0)*weights2;
norm += jointNMat[int(joints2)]*vec4(normal,1.0)*weights2;
tang4 +=  jointNMat[int(joints2)]*vec4(tangent,1.0)*weights2;
spotcoord0=lightmat0*vec4(pos.xyz,1.0);
pos = worldView * vec4(pos.xyz, 1.0);
norm = worldInverseTranspose * vec4(norm.xyz, 1.0);
tang = (worldInverseTranspose*vec4(tang4.xyz,1.0)).xyz;
gl_Position = projection * pos;
gl_PointSize=1.00000;
eyevec = -pos.xyz;
t = normalize(tang);n = normalize(norm.rgb);b = normalize(cross(n,t));teyevec.x = dot(eyevec, t);teyevec.y = dot(eyevec, b);teyevec.z = dot(eyevec, n);vec3 tmplightvec0 = -lightdir0;
tlightvec0.x = dot(tmplightvec0, t);tlightvec0.y = dot(tmplightvec0, b);tlightvec0.z = dot(tmplightvec0, n);lightvec0 = tmplightvec0;lightdist0 = length(lightpos0.xyz-pos.xyz);
vec4 texturePos;
textureCoords0=vec3(0.0,0.0,0.0);
texturePos=vec4(vec2(UVCoord[2],(1.0-UVCoord[3])),1.0,1.0);
textureCoords0=(layer0Matrix * texturePos).xyz;
}