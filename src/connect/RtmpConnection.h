//
//  NetConnection.h
//  AVSession
//
//  Created by whw on 2016/11/1.
//  Copyright © 2016年 meixin. All rights reserved.
//
#ifndef RtmpConnection_h
#define RtmpConnection_h
#include "../AVDefine.h"
#include "../base/thread.h"
#include "librtmp/rtmp.h"
#include <list>

typedef enum {
	Connection_Up,
	Connection_Down,
}ConnectionType;

typedef enum {
	Connection_Succuss,
	Connection_Fail, //网络 或者 服务器 ip port 错误
	Connection_Exception, //网络异常中断  这里会自动重连
	Stream_Fail,     //创建流失败
}ConnectionStatus;

enum RTMP_STATUS
{
	RTMP_Inited,
	RTMP_Connected,
	RTMP_Closed
};

class ConnectionHandle:public Reporter
{
public:
	virtual void onConnectionStatus(int uid, ConnectionStatus res) = 0;
	virtual void onReceiveFrame(int uid, MediaFrame& frame) = 0;
	virtual void onBandwidth(int uid,int stat) = 0;
};
struct RTMP;
class RtmpConnection :public Thread
{
public:
	RtmpConnection(ConnectionType type, ConnectionHandle* callback,int uid,std::string& uri);
	~RtmpConnection();

	void enableAudio(bool flag);
	bool enableAudio();

	void enableVideo(bool flag);
	bool enableVideo();

	void sendFrame(MediaFrame& frame);
protected:
	virtual void Run();
private:
	int connectRtmp();
	void closeRtmp();
	void setChunkSize(int size);
	int handle_output();
	int handle_input();
	void stat_bytes(int len);
	void processPackets();
	void doVideoFrameDelay(bool bBFramesOnly);
private:
	ConnectionHandle* _callback;

	BOOL    _running;
	RTMP_STATUS		_rtmp_status;
	BOOL    _iFrameRequired;
	RTMP*   _rtmp;
	int     _streamid;
	long    _starttime;
	std::string   _uri;
	std::list<RTMPPacket> _mediaData[NumOfMedia];
	CMutex  _mutex[NumOfMedia];
	int     _type;
	int     _uid;
	BOOL    _enableVideo;
	BOOL    _enableAudio;

	int     _sleepms;

	//drop packet
	uint32_t    _minFrameDropTs;
	uint32_t    _lastBFrameDropTs;

	//bandwidth stat
	float			total_byte_count_;
	long		    begin_stat_bw_time_;
	long            total_idle_time_;
	long            last_begin_idle_time_;
	float			last_stat_bw_;
	float			measure_stat_bw_;
};

#endif // !NetConnection_h

