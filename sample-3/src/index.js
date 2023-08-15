import video from "./video.js";
const Tools = {
    ...video
}
window.Tools = Tools;



function loadWASM() {
    import('./sample_video.js').then(res => {
        // res.Module.onRuntimeInitialized = function() {
        //     console.log("onRuntimeInitialized", res);
        // }
    }).catch(err => {
        console.log("engine init error", err);
    })
}

setTimeout(loadWASM, 500);

  







