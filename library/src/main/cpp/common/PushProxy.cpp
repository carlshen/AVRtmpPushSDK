//
// Created by 阳坤 on 2020-07-17.
//

#include "PushProxy.h"


IPush *PushProxy::getPushEngine() {
    return this->rtmpPush;
}

PushProxy::PushProxy() {
}


PushProxy *PushProxy::getInstance() {
    static PushProxy proxy[1];
    return &proxy[0];
}

void PushProxy::init(const char *url, JavaCallback **javaCallback) {
    this->url = url;
    this->javaCallback = *javaCallback;
    this->rtmpPush = new RTMPPush(url, javaCallback);
}

void PushProxy::start() {
    if (getPushEngine()) {
        getPushEngine()->start();
    }
}

void PushProxy::stop() {
    if (getPushEngine()) {
        if (getPushEngine()->isPush()) {
            getPushEngine()->stop();
        }
    }
    if (javaCallback) {
        delete (javaCallback);
    }
}
void PushProxy::release() {
    if (getPushEngine()) {
        if (getPushEngine()->isPush()) {
            getPushEngine()->stop();
        }
        getPushEngine()->relase();
        delete (this->getPushEngine());
    }

    if (javaCallback) {
        delete (javaCallback);
    }
}

void PushProxy::pushSpsPps(uint8_t *sps, int sps_len, uint8_t *pps, int pps_len) {
    if (getPushEngine() && getPushEngine()->isPush()) {
        getPushEngine()->pushSpsPps(sps, sps_len, pps, pps_len);
    }
}



void PushProxy::pushVideoData(uint8_t *video, int len, int keyframe) {
    if (getPushEngine() && getPushEngine()->isPush()) {
        getPushEngine()->pushVideoData(video, len, keyframe);
    }
}

void PushProxy::pushAudioData(uint8_t *audio, int len, int type) {
    if (getPushEngine() && getPushEngine()->isPush()) {
        getPushEngine()->pushAudioData(audio, len,type);
    }
}



