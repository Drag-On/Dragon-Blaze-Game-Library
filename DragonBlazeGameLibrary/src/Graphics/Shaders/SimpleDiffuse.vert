uniform mat4 m_mvp;
uniform mat4 m_itmv;
attribute vec3 v_vertex;
attribute vec3 v_color;
attribute vec3 v_normal;
varying vec3 var_v_color;
varying vec3 var_v_normal;

void main(void)
{
	gl_Position = m_mvp  * vec4(v_vertex, 1.0);
	var_v_color = v_color;
	var_v_normal = normalize(vec3(m_itmv * vec4(v_normal, 1.0)));
}