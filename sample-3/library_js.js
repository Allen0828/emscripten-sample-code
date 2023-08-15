mergeInto(LibraryManager.library, {
  set_texture_id: function(glTexture) {
    window.Tools.set_video_texture(glTexture);
    GLctx.bindTexture(GLctx.TEXTURE_2D, GL.textures[glTexture]);
    GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, true);
    const u8 = new Uint8Array(4);
    u8[0] = 255;
    u8[1] = 0;
    u8[2] = 0;
    u8[3] = 255;
    GLctx.texImage2D(GLctx.TEXTURE_2D, 0, GLctx.RGBA, 1, 1, 0, GLctx.RGBA, GLctx.UNSIGNED_BYTE, u8);
    GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, false)
  },
  video_update: function() {
    window.Tools.update_vidoe(GLctx, GL);
  }





});
