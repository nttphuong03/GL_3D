attribute vec3 a_posL;
attribute vec4 a_color;
attribute vec2 a_uv;


varying vec2 v_uv;
varying vec4 v_color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_Projection * u_View * u_Model * vec4(a_posL, 1);
v_color = a_color;
v_uv = a_uv;
}
   