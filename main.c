void vid_vsync() {
    while (REG_VCOUNT < 160);
}