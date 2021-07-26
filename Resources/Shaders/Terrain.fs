precision mediump float;
varying vec2 v_uv;
varying vec4 v_color;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform sampler2D blendTexture;

void main()
{
	gl_FragColor = texture2D(texture1, v_uv);
}
