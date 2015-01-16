
/*
 * Copyright (C) Roman Arutyunyan
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_rtmp_bandwidth.h"
#include "ngx_rtmp.h"


void
ngx_rtmp_update_bandwidth(ngx_rtmp_bandwidth_t *bw, uint32_t bytes)
{
    bw->bytes += bytes;
    bw->intl_bytes += bytes;

    ngx_rtmp_update_stat(bw);
}

void
ngx_rtmp_update_frame(ngx_rtmp_bandwidth_t *bw, uint32_t frames)
{
    bw->frames += frames;
    bw->intl_frames += frames;

    ngx_rtmp_update_stat(bw);
}

void
ngx_rtmp_update_stat(ngx_rtmp_bandwidth_t *bw)
{
    if (ngx_cached_time->sec > bw->intl_end) {
        bw->bandwidth = bw->intl_bytes / ngx_rtmp_stat_interval;
        bw->fps = bw->intl_frames / ngx_rtmp_stat_interval;
        bw->intl_bytes = 0;
        bw->intl_frames = 0;
        bw->intl_end = ngx_cached_time->sec + ngx_rtmp_stat_interval;
    }
}