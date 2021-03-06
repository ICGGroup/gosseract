#if __FreeBSD__ >= 10
#include "/usr/local/include/tesseract/baseapi.h"
#include "/usr/local/include/leptonica/allheaders.h"
#else
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#endif

#include "tessbridge.h"

TessBaseAPI Create() {
  tesseract::TessBaseAPI * api = new tesseract::TessBaseAPI();
  return (void*)api;
}

void Free(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  api->End();
  delete api;
}

int Init(TessBaseAPI a, char* tessdataprefix, char* languages) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  return api->Init(tessdataprefix, languages);
}

int Init(TessBaseAPI a, char* tessdataprefix, char* languages, char* configfilepath) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  if (configfilepath != NULL) {
    char *configs[]={configfilepath};
    int configs_size = 1;
    return api->Init(tessdataprefix, languages, tesseract::OEM_DEFAULT, configs, configs_size, NULL, NULL, false);
  } else {
    return api->Init(tessdataprefix, languages);
  }
}

bool SetVariable(TessBaseAPI a, char* name, char* value) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  return api->SetVariable(name, value);
}

void SetImage(TessBaseAPI a, char* imagepath) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  Pix *image = pixRead(imagepath);
  api->SetImage(image);
}

void SetImageFromBuffer(TessBaseAPI a, unsigned char* data, int size) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  Pix *image = pixReadMem(data, (size_t)size);
  api->SetImage(image);
}

void SetPageSegMode(TessBaseAPI a, int m) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  tesseract::PageSegMode mode = (tesseract::PageSegMode)m;
  api->SetPageSegMode(mode);
}

int GetPageSegMode(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  return api->GetPageSegMode();
}

char* UTF8Text(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  return api->GetUTF8Text();
}

char* HOCRText(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  return api->GetHOCRText(0);
}

char* TSVText(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  return api->GetTSVText(0);
}

int Orientation(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  tesseract::Orientation orientation;
  tesseract::WritingDirection direction;
  tesseract::TextlineOrder order;
  float deskew_angle;
    api->Recognize(0);

  tesseract::PageIterator* it =  api->AnalyseLayout();
  it->Orientation(&orientation, &direction, &order, &deskew_angle);
  //printf("Orientation: %d;\nWritingDirection: %d\nTextlineOrder: %d\nDeskew angle: %.4f\n", orientation, direction, order, deskew_angle);

  return orientation; //sprintf("Orientation: %d;\nWritingDirection: %d\nTextlineOrder: %d\nDeskew angle: %.4f\n", orientation, direction, order, deskew_angle); ;
}

const char* Version(TessBaseAPI a) {
  tesseract::TessBaseAPI * api = (tesseract::TessBaseAPI*)a;
  const char* v = api->Version();
  return v;
}
