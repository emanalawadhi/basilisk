/*
 ISC License

 Copyright (c) 2021, Autonomous Vehicle Systems Lab, University of Colorado at Boulder

 Permission to use, copy, modify, and/or distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.


 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

 */
%module simpleInstrumentController
%{
#include "simpleInstrumentController.h"
%}

%include "swig_conly_data.i"
%constant void Update_simpleInstrumentController(void*, uint64_t, uint64_t);
%ignore Update_simpleInstrumentController;
%constant void SelfInit_simpleInstrumentController(void*, uint64_t);
%ignore SelfInit_simpleInstrumentController;
%constant void Reset_simpleInstrumentController(void*, uint64_t, uint64_t);
%ignore Reset_simpleInstrumentController;

%include "simpleInstrumentController.h"

%include "architecture/msgPayloadDefC/AttGuidMsgPayload.h"
struct AttGuidMsg_C;
%include "architecture/msgPayloadDefC/AccessMsgPayload.h"
struct AccessMsg_C;
%include "architecture/msgPayloadDefC/DeviceCmdMsgPayload.h"
struct DeviceCmdMsg_C;
%include "architecture/msgPayloadDefC/DeviceStatusMsgPayload.h"
struct DeviceStatusMsg_C;

%pythoncode %{
import sys
protectAllClasses(sys.modules[__name__])
%}
