/*
    MIT License

    Copyright (c) 2018 WigWag Inc.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/*
 * client_logger.h
 *
 *  Created on: Sep 5, 2015
 *      Author: ed
 * (c) 2015, WigWag Inc.
 */
#ifndef CLIENT_LOGGER_H_
#define CLIENT_LOGGER_H_

#ifndef GREASE_CLIENT_ONLY
#define GREASE_CLIENT_ONLY 1
#endif

#include "nan.h"

#include "grease_client.h"

namespace Grease {




class GreaseLoggerClient : public Nan::ObjectWrap {
public:


	struct Opts_t {
		uv_mutex_t mutex;
		bool show_errors;
		bool callback_errors;
//		int bufferSize;  // size of each buffer
//		int chunkSize;
		uint32_t levelFilterOutMask;
		bool defaultFilterOut;
		int maxSinkErrors;
		Nan::Callback *onSinkFailureCB;
		uint32_t defaultOriginId;  // the origin ID to use if one is not provided.

		Opts_t() : show_errors(false), callback_errors(false), levelFilterOutMask(0), defaultFilterOut(false),
		 	 maxSinkErrors(SINK_MAX_ERRORS), onSinkFailureCB(NULL), defaultOriginId(0)
		{
			uv_mutex_init(&mutex);
		}

		void lock() {
			uv_mutex_lock(&mutex);
		}

		void unlock() {
			uv_mutex_unlock(&mutex);
		}

	};
	Opts_t Opts;


protected:
	static GreaseLoggerClient *CLIENT;  // this class is a Singleton
	int sinkErrorCount;
	int greaseConnectMethod;
	bool sinkFailureNeedsCall;

public:
	int log(const logMeta &f, const char *s, int len); // does the work of logging (for users in C++)

	static void Shutdown();
	static void Init(v8::Local<v8::Object> exports);

    static NAN_METHOD(New);
//    static Handle<Value> NewInstance(const Arguments& args);

    static NAN_METHOD(SetGlobalOpts);

    static NAN_METHOD(Start);

    static NAN_METHOD(Log);

    static NAN_METHOD(Flush);

    static Nan::Persistent<Function> constructor;


//	void setErrno(int _errno, const char *m=NULL) {
//		err.setError(_errno, m);
//	}

protected:

	static int _log( const logMeta *meta, const char *s, int len);

    GreaseLoggerClient() :
    	Opts(), sinkErrorCount(0), greaseConnectMethod(GREASE_NO_CONNECTION),
    	sinkFailureNeedsCall(false)
    	{
    	    CLIENT = this;
    	}

    ~GreaseLoggerClient() {
    }

public:
	static GreaseLoggerClient *setupClass() {
		if(!CLIENT) {
			CLIENT = new GreaseLoggerClient();
			atexit(shutdown);
		}
		return CLIENT;
	}


	static void shutdown() {
		setupClass();
		grease_shutdown();
	}
};




} // end namepsace




#endif /* CLIENT_LOGGER_H_ */
