varying vec4 fcolor;

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in vec4 color;

void main()
{
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * position;

	fcolor = color;
}
