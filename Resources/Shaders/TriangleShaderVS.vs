attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;

varying vec3 v_color;
varying vec3 v_pos;
varying vec2 v_uv;
uniform sampler2D u_s_texture;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = posL;
v_color = a_color;
v_uv = a_uv;
}
   