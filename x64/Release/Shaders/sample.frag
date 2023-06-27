#version 330 core


uniform vec3 objectColor;
out vec4 FragColor; //pixel color

uniform sampler2D tex0;

in vec2 texCoord;

void main(){
		//FragColor = vec4(0.4f, 0f, 0f, 1f);

		    //FragColor.rgb = objectColor;
			//FragColor.a = 1.0f;

		//Assigns texture color using the function
		FragColor = texture(tex0, texCoord);
}

