#version 330 core


uniform vec3 objectColor;
out vec4 FragColor; //pixel color

uniform sampler2D tex0;

in vec2 texCoord;

//Normal Data
in vec3 normCoord;

//Vertex position in World space
in vec3 fragPos;


uniform vec3 lightPos; //Lightning position
uniform vec3 lightColor; //Color position

uniform float ambientStr; //Strength of ambient light
uniform vec3 ambientColor; //Color of ambient light

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

void main(){
		vec3 normal = normalize(normCoord);  //Normalize the received normals
		vec3 lightDir = normalize(lightPos - fragPos);

		vec3 ambientCol = ambientColor * ambientStr;

		vec3 viewDir = normalize(cameraPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, normal);

		float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
		vec3 specColor = spec * specStr * lightColor;

		float diff = max(dot(normal, lightDir), 0.0); //Apply the diffuse formula
		vec3 diffuse = diff * lightColor; //Multiply it to the desired light color


		//FragColor = vec4(0.4f, 0f, 0f, 1f);

		    //FragColor.rgb = objectColor;
			//FragColor.a = 1.0f;

		//Assigns texture color using the function, then applies lightning
		FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex0, texCoord);


}

