uniform mat4 m_mvp;
uniform mat4 m_itmv;
attribute vec3 v_vertex;
attribute vec3 v_color;
attribute vec3 v_normal;
attribute vec2 v_uv;
varying vec3 var_v_color;
varying vec3 var_v_normal;
varying vec2 var_v_uv;

void main(void)
{
	gl_Position = m_mvp  * vec4(v_vertex, 1.0);
	var_v_color = v_color;
	var_v_normal = normalize(vec3(m_itmv * vec4(v_normal, 1.0)));
	var_v_uv = v_uv;
}