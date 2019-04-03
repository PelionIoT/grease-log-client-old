/*
 * Copyright (c) 2018, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
