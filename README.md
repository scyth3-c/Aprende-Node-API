# Node.js API Addons

mira conmigo los addons en Node.js en español, estare construyendo poco a poco este repositorio sobre Node.js y la implementacion de la Node_API para usar C++ en este entorno de ejecucion [Node.js](https://github.com/nodejs)

**¿Como esta repartido todo esto?**

en los ejemplos cada uno tendra su readme con los paso a pasos, explicados y con el codigo fuente para probar directamente, aqui en este readme solo encontraras ideas generales y explicaciones no tan especificas.


## Node_API

**¿Por que Node_API y no NAN o cualquier otra?** 

especificamente Node_API tiene ventajas sobre por ejemplo NAN como no estar ligado directamente al motor [V8.js](https://github.com/v8/v8) esta tiene una capa de abstraccion sobre este, por ende no toca modificar el addon o el codigo cada vez que lo hace el motor, esta "desligado" por mas que cambie el motor esta seguira funcionado por ejemplo en caso de una integracion con [ChakraCore](https://github.com/chakra-core/ChakraCore) del que se habla


**¿Tengo que tener instalado o instalar V8.js?**

no, debido a la naturaleza de la Node_API  y Node.js basta con instalar el "puente" [node-gyp](https://github.com/nodejs/node-gyp) de la siguiente manera: 


```javascript

 npm install -g node-gyp

```

en el caso de NAN por ejemplo habria que instalar el paquete **nan** de manera local para el proyecto (sin usar -g)


**¿Para que o que usos tendria usar estos addos, casos de uso?**

bueno la principal razon es poner a disposicion todas las bibliotecas, propiedades y poder disponible en C++ para programadores de JavaScript tambien permite integrar codigo C++ existente aprovechandolo, refinandolo y manteniendolo. una integracion C++ / JavaScript 



### extra

asumire que tienes instalado Node.js y conoces lo basico de este entorno de ejecucion, como escribir y ejecutar programas en javascript typescript ETC.