/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4; c-file-style:"stroustrup" -*-
**
** Copyright (C) 1995-2009 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
*/

#ifndef VEGARASTERIZER_H
#define VEGARASTERIZER_H

#ifdef VEGA_SUPPORT
#include "modules/libvega/vegafixpoint.h"

class VEGAPath;

// Span generated by the rasterizer.
// Starting at position (pos, scanline) and extending to
// (pos+length-1, scanline). mask points to coverage (alpha) values for
// the span, and mask == NULL implies an opaque span
// NOTE/FIXME: Currently only caring about fully opaque spans - could
// extend to work with "single opacity" spans
struct VEGASpanInfo
{
	unsigned scanline;
	unsigned pos;

	const UINT8* mask;		// mask == NULL => opaque span
	unsigned length;
};

class VEGASpanConsumer
{
public:
	virtual ~VEGASpanConsumer() {}

	virtual void drawSpans(VEGASpanInfo* raster_spans, unsigned int span_count) = 0;
};

class VEGARasterizer
{
public:
	VEGARasterizer();
	~VEGARasterizer();

	OP_STATUS initialize(unsigned int w, unsigned int h);

	void setConsumer(VEGASpanConsumer* con) { consumer = con; }
	void setXORFill(bool xf) { xorFill = xf; }
	void setQuality(unsigned int q);
	void setRegion(int cr_sx, int cr_sy, int cr_ex, int cr_ey)
	{
		cliprect_sx = cr_sx;
		cliprect_sy = cr_sy;
		cliprect_ex = cr_ex;
		cliprect_ey = cr_ey;
	}

	OP_STATUS rasterize(const VEGAPath* path);

	unsigned calculateArea(VEGA_FIX minx, VEGA_FIX miny, VEGA_FIX maxx, VEGA_FIX maxy);

	void rasterRect(unsigned x, unsigned y, unsigned w, unsigned h);
	void rasterRectMask(unsigned x, unsigned y, unsigned w, unsigned h,
						const UINT8* mask, unsigned maskStride);

	UINT8* getMaskScratch() const { return maskscratch; }

private:
	enum
	{
		MAX_RASTER_SPANS		= 32,	// The maximum number of spans in a batch
		MIN_RASTER_SPAN_LENGTH	= 32	// The minimum length of an opaque span
	};

	void emitMonotoneSpan(struct VEGASpanState& state);
	void emitMaskSpan(struct VEGASpanState& state);
	void addSpans(unsigned int line, const struct VEGAIntervalList& ilist);

	void scanForSpans(unsigned line, int start, unsigned int length);

	void emitSpan(const VEGASpanInfo& span);
	void emitSpanAndFlush(VEGASpanInfo& span);

	void flushSpans();

	VEGASpanInfo* raster_spans;
	unsigned int span_count;

	UINT8* maskscratch;
	UINT8* maskbuffer_ptr;

	unsigned int remainingMaskBuffer() const { return maskscratch - maskbuffer_ptr; }

	struct VEGASortedLineList *sortedlines;
	unsigned int allocSortedLines;
	UINT8 *maskbuffer;
	struct VEGALineQueue* sleepingScanlines;
	struct VEGACoverageData* line_bucket;

	bool xorFill;
	unsigned int quality;
	int cliprect_sx;
	int cliprect_sy;
	int cliprect_ex;
	int cliprect_ey;

	// These are actually "max. scanlines" and "max. columns"
	unsigned width;
	unsigned height;

	VEGASpanConsumer* consumer;
};

#endif // VEGA_SUPPORT
#endif // VEGARASTERIZER_H
