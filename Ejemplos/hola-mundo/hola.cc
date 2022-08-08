#include <node_api.h>


static napi_value  CUERPO_DEL_METODO(napi_env env, napi_callback_info info) 
{
  napi_status estado;
  napi_value cuerpo;
  
  int total_caracteres = 10;

  estado = napi_create_string_utf8(env, "hola mundo", total_caracteres , &cuerpo);
  return cuerpo;
}

#define DECLARAR_METODO(nombre, funcion)                                        \
  { nombre, 0, funcion, 0, 0, 0, napi_default, 0 }


static napi_value   INICIADOR(napi_env env, napi_value exports) 
{
  napi_status estado;
  napi_property_descriptor desc = DECLARAR_METODO("nombre_en_js", CUERPO_DEL_METODO);
  estado = napi_define_properties(env, exports, 1, &desc);
  return exports;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, INICIADOR)