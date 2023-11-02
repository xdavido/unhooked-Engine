#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "MathGeoLib/include/Math/Quat.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	X = float3(1.0f, 0.0f, 0.0f);
	Y = float3(0.0f, 1.0f, 0.0f);
	Z = float3(0.0f, 0.0f, 1.0f);

	Position = float3(0.0f, 10.0f, 5.0f);
	Reference = float3(0.0f, 0.0f, 0.0f);
	ViewMatrix = IdentityMatrix;

	CalculateViewMatrix();
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
    App->editor->AddToConsole("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");
    App->editor->AddToConsole("Cleaning Camera");
	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
    float3 newPos(0, 0, 0);
    float speed = 1.0f * dt;
    float zoomspeed = 0.0f * dt;

    if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
    {
        // Adjust zoom speed when Ctrl is pressed
        zoomspeed = 25.0f * dt;
    }

    if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
    {
        int dx = -App->input->GetMouseXMotion();
        int dy = App->input->GetMouseYMotion();

        float moveSpeed = 1.0f * dt;

        // Calculate the movement vector based on mouse input
        float3 moveVector = X * (dx * moveSpeed) + Y * (dy * moveSpeed);

        // Update the camera's position and reference
        Position += moveVector;
        Reference += moveVector;
    }
    if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
    {
        // Reset the camera's position to (0, 0, 0)
        Position = float3(0.0f, 0.0f, 0.0f);
    }

    // Mouse wheel zoom
    if (App->input->GetMouseZ() != 0)
    {
        // Get the mouse wheel delta
        int wheelDelta = App->input->GetMouseZ();

        // Adjust the camera's position based on the wheelDelta
        float3 zoomVector = Z * (wheelDelta * zoomspeed);
        Position -= zoomVector;
    }

    if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
    {
        int dx = -App->input->GetMouseXMotion();
        int dy = -App->input->GetMouseYMotion();

        float Sensitivity = 0.35f * dt;

        // Define the custom reference point. This will be the position of the object
        float3 customReference(1.0f, 1.0f, 1.0f);

        // Calculate the position relative to the custom reference point
        float3 relativePosition = Position - customReference;

        if (dx != 0)
        {
            float DeltaX = (float)dx * Sensitivity;

            float3 rotationAxis(0.0f, 1.0f, 0.0f);
            Quat rotationQuat = Quat::RotateAxisAngle(rotationAxis, DeltaX);

            // Apply rotation to the position relative to the custom reference point
            relativePosition = rotationQuat * relativePosition;
        }

        if (dy != 0)
        {
            float DeltaY = (float)dy * Sensitivity;

            Quat rotationQuat = Quat::RotateAxisAngle(X, DeltaY);

            // Apply rotation to the relative position
            relativePosition = rotationQuat * relativePosition;
        }

        // Update the camera's Position based on the custom reference point
        Position = customReference + relativePosition;
    }

    if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
        speed = 8.0f * dt;

    if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
    if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

    if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
    if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;

    if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
    if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

    Position += newPos;
    Reference += newPos;

    if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
    {
        int dx = -App->input->GetMouseXMotion();
        int dy = -App->input->GetMouseYMotion();

        float Sensitivity = 0.35f * dt;

        Position -= Reference;

        if (dx != 0)
        {
            float DeltaX = (float)dx * Sensitivity;

            float3 rotationAxis(0.0f, 1.0f, 0.0f);
            Quat rotationQuat = Quat::RotateAxisAngle(rotationAxis, DeltaX);

            X = rotationQuat * X;
            Y = rotationQuat * Y;
            Z = rotationQuat * Z;
        }

        if (dy != 0)
        {
            float DeltaY = (float)dy * Sensitivity;

            Quat rotationQuat = Quat::RotateAxisAngle(X, DeltaY);

            Y = rotationQuat * Y;
            Z = rotationQuat * Z;

            if (Y.y < 0.0f)
            {
                Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
                Y = Z.Cross(X);
            }
        }

        Position = Reference + Z * Position.Length();
    }

    LookAt(Reference);

    CalculateViewMatrix();

    return UPDATE_CONTINUE;
}
// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3&Position, const float3&Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = (Position - Reference).Normalized();
	X = (float3(0.0f, 1.0f, 0.0f).Cross(Z)).Normalized();
	Y = Z.Cross(X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const float3&Spot)
{
	Reference = Spot;

	Z = (Position - Reference).Normalized();
	X = (float3(0.0f, 1.0f, 0.0f).Cross(Z)).Normalized();
	Y = Z.Cross(X);

	CalculateViewMatrix();
}



// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3&Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return ViewMatrix.M;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	//todo: USE MATHGEOLIB here BEFORE 1st delivery! (TIP: Use MathGeoLib/Geometry/Frustum.h, view and projection matrices are managed internally.)
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -(X.Dot(Position)), -(Y.Dot(Position)), -(Z.Dot(Position)), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);

}