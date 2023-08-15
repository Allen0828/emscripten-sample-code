
var video_texture;

const video = document.createElement("video");
video.playsInline = true;
video.muted = true;
video.loop = true;
video.src = "dance.mp4";
video.play();
video.oncanplay = () => {
    
    console.log("on", video.videoWidth, video.videoHeight)
}



const autoPlayAfterAnyClick = () => {
    video.muted = false;
    console.log(video.videoWidth)
    document.removeEventListener('click', autoPlayAfterAnyClick);
};

document.addEventListener('click', autoPlayAfterAnyClick);


export default {

    set_video_texture(gid) {
        video_texture = gid
    },
    update_vidoe(GLctx, GL) {
        GLctx.bindTexture(GLctx.TEXTURE_2D, GL.textures[video_texture]);
        // UNPACK_FLIP_Y_WEBGL 
        // GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, true);
        GLctx.texImage2D(GLctx.TEXTURE_2D, 0, GLctx.RGBA, video.videoWidth, video.videoHeight, 0, GLctx.RGBA, GLctx.UNSIGNED_BYTE, video);
    }

}


