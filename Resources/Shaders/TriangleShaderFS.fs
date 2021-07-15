precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_s_texture;

float near = 0.1;
float far  = 100.0;
float LinearizeDepth(float depth)
{
	float z = depth*2.0 - 1.0;
	return (2.0 * near * far)/ (far + near - z *(far - near));
}
void main()
{
	gl_FragColor = texture2D(u_s_texture, v_uv);
}
