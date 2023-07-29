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
	app.current_scene()->light()->set_enabled(true);

	app.texture_factory()->load("models/hasan/hasan.jpg", "hasan");

	app.physics_engine()->bind_physics_tick_callback([&](double delta){
		if(app.current_scene())
		{
			float intensity = app.current_scene()->light()->ambient_instensity();
			constexpr const float step = 0.0166f * 0.2f;
			static int direction = 1;
			
			intensity += (step * direction);
			if(intensity > 1.0f)
			{
				intensity = 1.0f;
				direction *= -1;
			}
			else if(intensity < 0.0f)
			{
				intensity = 0.0f;
				direction *= -1;
			}

			app.current_scene()->light()->set_ambient_intensity(intensity);
		}
	});

	nle::Model mod_minecraft_block(nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	mod_minecraft_block.load_obj("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj");

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	// Gather noise data
	std::vector<float> noiseData(128 * 128);
	int index = 0;
	float multiplier = 10.f;

	for (int y = 0; y < 128; y++)
	{
		for (int x = 0; x < 128; x++)
		{
			// noiseData[index++] = noise.GetNoise((float)x, (float)y);
			auto * mm = mod_minecraft_block.create_instance();
			app.current_scene()->add_child(mm);
			mm->set_position({x, multiplier * noise.GetNoise((float)x, (float)y), y});
		}
	}
	
	// nle::Model modHasan(nle::DEFAULT_SHADER, app.texture_factory()->get("hasan"));
	// if(modHasan.load_obj("models/hasan/hasan.obj"))
	// {
	// 	for(int i = 0; i < 10; i++)
	// 	{
	// 		auto rnd = glm::sphericalRand(200.f);
	// 		nle::MultiMeshInstance *mm = modHasan.create_instance();
	// 		// mm->set_position(rnd + glm::vec3(0.f, 1000.f, 0.f));
	// 		mm->set_scale(glm::vec3(50.f));
	// 		app.current_scene()->add_child(mm);
	// 		// app.physics_engine()->attach_physics_body(mm);
	// 	}
	// }

	app.run();

	return (0);
}
