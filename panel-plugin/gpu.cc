/*
 * GPU load reading for XFCE system load plugin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpu.h"

gulong read_gpu0load()
{
    /* Use nvidia-smi for Nvidia GPU monitoring */
    const char *command = "nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        usage = atoi(buffer);
    }
    pclose(fp);
    return usage;
}

gulong read_gpu1load()
{
    /* Use nvidia-smi for Nvidia GPU monitoring */
    const char *command = "nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    int gpu_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && gpu_count < 2) {
        if (gpu_count == 1) {
            usage = atoi(buffer);
            break;
        }
        gpu_count++;
    }
    pclose(fp);
    return usage;
}

gulong read_vram0usage()
{
    /* Use nvidia-smi for Nvidia VRAM monitoring */
    const char *command = "nvidia-smi --query-gpu=memory.used,memory.total --format=csv,noheader,nounits 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        gulong used_mb, total_mb;
        if (sscanf(buffer, "%lu, %lu", &used_mb, &total_mb) == 2 && total_mb > 0) {
            usage = (used_mb * 100) / total_mb;
        }
    }
    pclose(fp);
    return usage;
}

gulong read_vram1usage()
{
    /* Use nvidia-smi for Nvidia VRAM monitoring */
    const char *command = "nvidia-smi --query-gpu=memory.used,memory.total --format=csv,noheader,nounits 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    int gpu_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && gpu_count < 2) {
        if (gpu_count == 1) {
            gulong used_mb, total_mb;
            if (sscanf(buffer, "%lu, %lu", &used_mb, &total_mb) == 2 && total_mb > 0) {
                usage = (used_mb * 100) / total_mb;
            }
            break;
        }
        gpu_count++;
    }
    pclose(fp);
    return usage;
}