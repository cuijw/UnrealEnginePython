#pragma once

#include "UnrealEnginePython.h"

#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"

#include "UEPyIHttpRequest.generated.h"


struct ue_PyIHttpBaseType;

typedef struct {
	ue_PyIHttpBase base;
	/* Type-specific fields go here. */
	TSharedRef<IHttpRequest> http_request;
} ue_PyIHttpRequest;


void ue_python_init_ihttp_request(PyObject *);

UCLASS()
class UPythonHttpDelegate : public UPythonDelegate
{
	GENERATED_BODY()

public:
	void OnRequestComplete(FHttpRequestPtr request, FHttpResponsePtr response, bool successful);

	void SetPyHttpRequest(ue_PyIHttpRequest *request) {
		py_http_request = request;
		Py_INCREF(py_http_request);
	}

	~UPythonHttpDelegate() {
		Py_XDECREF(py_http_request);
	}
protected:
	ue_PyIHttpRequest *py_http_request;
};
