
#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
uniform vec3 viewPos;

uniform mat4 sun_matrix;

// Output vertex attributes (to fragment shader)
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec4 fragColor;
out vec3 fragNormal;
out vec3 fragViewPos;



// NOTE: Add here your custom variables

void main()
{
    vec3 vertpos = vertexPosition;


    // Send vertex attributes to fragment shader
    fragPosition = vec3(matModel*vec4(vertpos, 1.0));
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    fragNormal = normalize(vec3(matNormal*vec4(vertexNormal, 1.0)));

    fragViewPos = viewPos;

 
    // Calculate final vertex position
    gl_Position = mvp*vec4(vertpos, 1.0);
}
