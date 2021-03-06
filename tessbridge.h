#ifdef __cplusplus
extern "C" {
#endif

typedef void* TessBaseAPI;
TessBaseAPI Create(void);
void Free(TessBaseAPI);
int Init(TessBaseAPI, char*, char*, char*);
bool SetVariable(TessBaseAPI, char*, char*);
void SetImage(TessBaseAPI, char*);
void SetImageFromBuffer(TessBaseAPI, unsigned char*, int);
void SetPageSegMode(TessBaseAPI, int);
int GetPageSegMode(TessBaseAPI);
char* UTF8Text(TessBaseAPI);
char* HOCRText(TessBaseAPI);
char* TSVText(TessBaseAPI);
int Orientation(TessBaseAPI);
const char* Version(TessBaseAPI);

#ifdef __cplusplus
}
#endif/* extern "C" */
