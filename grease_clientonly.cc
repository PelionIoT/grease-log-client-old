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

/**
 * (c) 2015 WigWag Inc.
 *
 * Author: ed
 */
#ifndef GREASE_CLIENT_ONLY
#define GREASE_CLIENT_ONLY 1
#endif
#include "logger.h"
#include "client_logger.h"

#include <v8.h>
#include <node.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "error-common.h"

using namespace node;
using namespace v8;

using namespace Grease;




NAN_METHOD(ErrorFromErrno) {
	Nan::EscapableHandleScope scope;

	if(info.Length() > 0 && info[0]->Int32Value()) {
		Local<Value> err = _errcmn::errno_to_JS(info[0]->Int32Value(),"netkit: ");
		scope.Escape(err);
	} else {
		scope.Escape(Nan::Undefined());
	}
}

//NAN_METHJNewLoggerClient(const Arguments& args) {
//	HandleScope scope;
//
//	return scope.Close(GreaseLoggerClient::NewInstance(args));
//
//}


void InitAll(Handle<Object> exports, Handle<Object> module) {

//	exports->Set(String::NewSymbol("newClient"), FunctionTemplate::New(NewLoggerClient)->GetFunction());

	GreaseLoggerClient::Init(exports);

	Handle<Object> errconsts = Nan::New<Object>();
	_errcmn::DefineConstants(errconsts);
	Nan::Set(exports,Nan::New<String>("ERR").ToLocalChecked(), errconsts);

}

NODE_MODULE(greaseLogClient, InitAll)
