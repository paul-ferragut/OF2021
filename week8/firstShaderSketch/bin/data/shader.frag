#version 120


uniform float u_time;

void main(){

float resolution=1000.0;

	vec2 st= gl_FragCoord.xy/resolution;


	//float left= step(0.2,st.x);
	//float bottom =step(0.2,st.y);

	vec2 bl=step(0.2,st);

	vec2 tr=step(0.2,1.0-st);



	vec3 color=vec3(bl.x*bl.y*tr.x*tr.y);

	gl_FragColor = vec4(color,1.0);

}