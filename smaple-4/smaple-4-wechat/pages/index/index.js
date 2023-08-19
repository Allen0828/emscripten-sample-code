// index.js
// 获取应用实例
const app = getApp()

Page({
    data: {
        canvas:{
            width:300,
            height:300
        },
        fps: 60
    },
    onLoad() {
        // 注意 webgl2 最低支持得版本为 2.24.0
    },
    onReady() {
        let that = this;
        const query = wx.createSelectorQuery()
        query.select('#myCanvas').node().exec((res) => {
            const canvas = res[0].node
            var gl = canvas.getContext('webgl2')
            gl.clearColor(1, 0, 1, 1)
            gl.clear(gl.COLOR_BUFFER_BIT)
            getApp().main_canvas = canvas;
            that.initEngine();
        })
    },
    initEngine: function() {
        // require('./wechat.js');
    },
})
