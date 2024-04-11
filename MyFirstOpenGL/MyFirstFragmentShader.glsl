#version 440 core

uniform vec2 windowSize;
uniform float u_Time;
uniform int isNotPyramid = 0;

out vec4 fragColor;

void main() {

    if(isNotPyramid == 1)
    {
        if(gl_FragCoord.y > (windowSize.y * 0.5))
	    {
		    fragColor = vec4(1.0, 0.8, 0.0, 1.0);
	    }
	    else
	    {
		    fragColor = vec4(1.0, 0.5, 0.2, 1.0);
	    } 
    }
    else
    {
    	float t = mod(u_Time, 6.0);
        vec3 color;

        if (t < 2.0) 
        {
            color = vec3(1.0, 0.0, 0.0);
        } 
        else if (t < 4.0) 
        {
            color = vec3(0.0, 0.0, 1.0);
        } 
        else 
        {
            color = vec3(0.0, 1.0, 0.0);
        }

            fragColor = vec4(color, 1.0);
    }
     

}
