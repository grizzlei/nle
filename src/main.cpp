#include "nle/Window.h"
#include "nle/Scene.h"
#include "nle/Renderer3D.h"
#include "nle/Texture.h"
#include "nle/Mesh.h"
#include "nle/Model.h"
#include "nle/Nle.h"

#include <glm/gtc/random.hpp>

#include "FastNoiseLite.h"

int main(int argc, char *argv[])
{
	nle::Nle app;

	app.current_scene()->camera()->set_position({0.f, 200.f, -200.f});
	app.current_scene()->camera()->set_rotation({0.f, 90.f, 0.f});
	app.current_scene()->light()->set_ambient_intensity(.05f);
	app.current_scene()->light()->set_diffuse_intensity(1.f);
	app.current_scene()->light()->set_rotation(glm::vec3(2.f, -1.f, -2.f));
	app.current_scene()->light()->set_enabled(false);

	app.texture_factory()->load("models/hasan/hasan.jpg", "hasan");

	app.physics_engine()->bind_physics_tick_callback([&](double delta){
		// if(app.current_scene())
		// {
		// 	float intensity = app.current_scene()->light()->ambient_instensity();
		// 	constexpr const float step = 0.0166f * 0.2f;
		// 	static int direction = 1;
			
		// 	intensity += (step * direction);
		// 	if(intensity > 1.0f)
		// 	{
		// 		intensity = 1.0f;
		// 		direction *= -1;
		// 	}
		// 	else if(intensity < 0.0f)
		// 	{
		// 		intensity = 0.0f;
		// 		direction *= -1;
		// 	}

		// 	app.current_scene()->light()->set_ambient_intensity(intensity);
		// }
	});

	nle::Model mod_minecraft_block(nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	mod_minecraft_block.load_obj("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj");

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	// noise.SetCellularReturnType(FastNoiseLite::CellularReturnType::CellularReturnType_Distance);

	// Gather noise data
	int size = 32;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int scaled_height = static_cast<int>((1.f + noise.GetNoise((float)x, (float)y)) * 10);
			for(int i = 0; i < scaled_height; i++)
			{
				auto * mm = mod_minecraft_block.create_instance();
				app.current_scene()->add_child(mm);
				app.current_scene()->register_render_object(mm);

				mm->set_position({x * 2, scaled_height * 2 - i * 2, y * 2});
			}
		}
	}

	prinf("%d blocks created", app.current_scene()->render_objects().size());

	app.run();

	return (0);
}
