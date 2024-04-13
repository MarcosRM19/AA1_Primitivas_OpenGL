Read me

1.CallBack functions:
-Intentamos crear una clase que se encargaran de iniciar el programa a la vez que se encargara de hacer resize de la ventana
el problema que surge fue el ver que el Resize_window es un CallBack y no sabemos como trabajar con estos fuera del main por lo 
que en el Source.cpp hay una función llamada InitProgram que contiene las comandas que queriamos que hiciese en la clase

-Lo mismo sucede con la llamada para realizar los inputs, que al ser un CallBack la trabajamos en el Source.cpp, aunque en este caso
todo lo que esta relacionado con los inputs y las reacciones a estos esta en el InputManager

2.Preguntas a IA

-En la línia de código "glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * GetPoint().size(), GetPointData(), GL_STATIC_DRAW);" antes trabajamos con que
los puntos de cada figura era un array pero ahora en nuestro proyecto es un vector de GLfloat, entonces a la hora de pasar la información de los puntos
recurrimos a preguntar como hacerlo ya que nos habiamos quedado en callado en la parte donde pone GetPointData(), en este caso la IA propuso implementar la 
función

GLfloat* Primitive::GetPointData()
{
	GLfloat* pointData = point.data();
	return pointData;
}

con la que conseguiamos la data del vector de puntos con el cual poder trabajar en la línia de código que estabamos bloqueados

-A la hora de calcular la velocidad también recurrimos a una IA para hacernos una idea de como hacerlo, en este caso la IA nos mostro la línia de código

float speed = 1.0f / (1000.0f / 16.0f);

donde explicaba que al final la base de la formula es V = X / t, en este caso la IA explica que lo que queremos es mover el objeto 1 unidad por segundo
por lo que la X es 1.0 y el cálculo de 1000 / 16 nace de querer pasar de milisegundos como son los 16.0f a segundos todo buscando un frecuencia de actualización de
60 frames por segundo, ya que el al hacer 1000/60FPS logramos los anteriores mencianonados 16 milisegundos 