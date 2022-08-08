# hola mundo

aqui veremos paso a paso como hacer el hola mundo usando los addons c++ con node, mas especificamente **napi** puedes ver mas acera de napi aqui [node_api](https://nodejs.github.io/node-addon-examples/about/what/)  pero en resumen  es un intermediario entre lo que es C++ y JavaScript de esta forma que podemos manipular y trabajar con este directamente con C++

<br/>
<hr />

## creacion, paso  a paso

- primero iniciaremos creado el proyecto de Node.js, para esto basta con  ``` npm init -y ``` que esto es lo basico para un proyecto Node.js donde vamos a implementar el addon.


- segundo, ahora sera necesario instalar node-gyp para establecer la vinculacion y definir los addons que se contruiran, para instalarlo lo haremos como cualquier otro paquete NPM

  ``` npm install -g node-gyp ```
  
    puede ser de manera global para instalarlo por fuera del proyecto, pero es opcional, y para utilizar los modulos de manera mas practica instalaremos "bindings"

     ``` npm install bindings ```
  
    y esto es lo que necesitamos, como mencione en el readme principal es aconsejable tener python instaldo y algun compilador C++


- tercero, crearemos un archivo .gyp los archivos de este tipo o extension se utiliza para orquestar la compilacion de proyectos en diferentes plataformas, en nuestro caso crearemos binding.gyp y dentro de este archivo vamos a colocar lo siguiente:

```json
 {
    "targets": [
        {
            "target_name": "hola",
            "sources": ["hola.cc"]
        }
    ] 
 } 
```

que si eres observador notaras que es un simple json que contiene un arreglo de los objetivos para compilar, dichos "objetivos" tienen tanto el nombre clave por el cual identificaremos luego en JavaScript y el "sources" que son los codigos fuentes que lo componen.


<hr/>

- cuarto, ahora crearemos el codigo fuente del addon .cc que en nuestro caso es hola.cc, esta explicacion sera algo larga asi que continua aqui abajo


    bien haremos algo sencillo como escribir hola mundo desde el addon, para esto vamos a crear dos **napi_value** cosa que veremos bastante, pero ahora no nos fijemos en eso, creamos de napi_value el cuerpo del metodo y otro para inicializarlo,  para empezar incluiremos la libreria necesaria (no es necesario instalarla)

 ``` #include <node_api.h> ``` 


 ahora vamos a ver como crear el cuerpo del addon de tipo **napi_value** estatico que recibe dos parametros 
 [node_env](https://nodejs.org/api/n-api.html#napi_env) para el contexto que la implementación de Node-API y el [napi_callback_info](https://nodejs.org/api/n-api.html#napi_callback_info) que es un tipo de puntero de función para funciones nativas, **de esto no de preocupes por ahora si no lo entiendes**



 ```c++
 
 static napi_value  cuerpo_metodo (napi_env env, napi_callback_info info)
 {

    napi_status estado;
    napi_value  cuerpo;

    int total_caracteres = 10;
    estado = napi_create_string_utf8(env, "hola mundo", total_caracteres, &cuerpo);

    return cuerpo;

 }
 
 ```


bien que es lo que hacemos en el codigo anterior, primero creamos una variable de tipo **napi_value** que guardara si la operacion que hicimos funciono o no, segundo usamos una sobrecarga de **napi_value** "cuerpo" que usaremos para crear una cadena adecuada para JavaScript, creamos una variable para guardar el total de caracteres de nuestro mensaje, ahora guardamos el resultado de napi_create_string_utf8 que retorna un **napi_status** y lo que hace es procesar la candena "hola mundo" al formato adecuado.

<hr/> <br/>
 
el siguiente paso es crear una macro para darle un formato mas legible al codigo siguiente, esta macro simplemente remplazar los valores en compilacion, como un alias pero a la hora de utilizar es mas limpio

```c++
#define DECLARAR_METODO(nombre, funcion)                                        \
  { nombre, 0, funcion, 0, 0, 0, napi_default, 0 }

```

<hr/> <br/>

ahora vamos hacer algo similiar a lo del principio, creamos un **napi_value** estatico, y de parameteos recibe  [node_env](https://nodejs.org/api/n-api.html#napi_env) para el contexto y otro **napi_value** que sera lo que exporte el motodo

```c++
static napi_value   INICIADOR(napi_env env, napi_value exports) 
{
  napi_status estado;
  napi_property_descriptor desc = DECLARAR_METODO("nombre_en_js", CUERPO_DEL_METODO);
  estado = napi_define_properties(env, exports, 1, &desc);
  return exports;
}

```


explicando lo que hicimos en el codigo anterior esta que creamos un **napi_status** para guardar el estado de la operacion que haremos, creamos un napi_property_descriptor  "desc" y aqui es donde usaremos la macro DECLARAR_METODO para darle el formado correccto como deberia pasarse,

 ```{ name, 0, func, 0, 0, 0, napi_default, 0 }```

ahora le asiganamos a estado el valor que devuelte napi_define_properties que dira si se realizo bien o no, lo interesante es que aqui usamos el export para aplicarle el cuerpo, para crear el metodo llamable en JavaScript en este caso "nombre_en_js"
y por ultimo retornamos exports que lo utilizaremos enseguida


por ultimos usamos la macro **NAPI_MODULE** para montar lo anterior como ya un modulo gyp 

```c++
NAPI_MODULE(NODE_GYP_MODULE_NAME, INICIADOR)
```

y compilamos y ejecutamos en la carpeta del moduloen este caso "hola-mundo"

```
$ node-gyp configure
$ node-gyp build
$ node ./app.js
```

primero preparamos el terreno para gyp, luego compilamos los modulos y por ultimo ejecutamos ya usandolo en Node

<br/><br/>

<h1>FIN</h1>
<h3>Gracias por leer! :)</h3>


<br/>
<br/>
<br/>
<hr/>

## Extra 

### funciones utilizadas

**Vision del Codigo Completo**

```c++
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
```


**napi_create_string_utf8**

```c++
napi_status napi_create_string_utf8(napi_env env,
                                    const char* str,
                                    size_t length,
                                    napi_value* result)
```
[documentacion](https://nodejs.org/api/n-api.html#napi_create_string_utf8)


<hr/> <br/>

**napi_define_properties**
```c++
napi_status napi_define_properties(napi_env env,
                                   napi_value object,
                                   size_t property_count,
                                   const napi_property_descriptor* properties);
```

[documentacion](https://nodejs.org/api/n-api.html#napi_define_properties)
