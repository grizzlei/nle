#include "nle/Window.h"
#include "nle/Scene.h"
#include "nle/Renderer3D.h"
#include "nle/Texture.h"
#include "nle/Mesh.h"
#include "nle/MultiMesh.h"
#include "nle/Model.h"
#include "nle/Nle.h"

#include <glm/gtc/random.hpp>

#include "FastNoiseLite.h"

int main(int argc, char *argv[])
{
	nle::Nle app;

	// app.current_scene()->camera()->set_position({0.f, 200.f, -200.f});
	app.current_scene()->camera()->set_rotation({0.f, 90.f, 0.f});
	app.current_scene()->light()->set_ambient_intensity(1.0f);
	app.current_scene()->light()->set_diffuse_intensity(1.f);
	app.current_scene()->light()->set_rotation(glm::vec3(2.f, -1.f, -2.f));
	app.current_scene()->light()->set_enabled(true);

	auto rla = app.renderer()->render_layer_attributes(nle::Renderer3D::RenderLayer::_0);
	rla.render_distance = 200;
	app.renderer()->set_render_layer_attributes(nle::Renderer3D::RenderLayer::_0, rla);

	// app.texture_factory()->load("models/hasan/hasan.jpg", "hasan");

	nle::Model mod_minecraft_block(nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	mod_minecraft_block.load_obj("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj");

	// nle::Model mod_hasan(nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/hasan/hasan.jpg", "hasan"));
	// mod_hasan.load_obj("models/hasan/hasan.obj");
	// auto *mmi = mod_hasan.create_instance();
	// mmi->set_scale(glm::vec3(100.f));

	// app.current_scene()->add_child(mmi);
	// app.current_scene()->register_render_object(mmi);



/////////////////////////////////////////////////////////////////////////////////////////////////////
	// FastNoiseLite noise;
	// noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	// int size = 256;
	// for (int y = 0; y < size; y++)
	// {
	// 	for (int x = 0; x < size; x++)
	// 	{
	// 		int scaled_height = static_cast<int>((1.f + noise.GetNoise((float)x, (float)y)) * 10);
	// 		auto * mm = mod_minecraft_block.create_instance();
	// 		app.current_scene()->add_child(mm);
	// 		app.current_scene()->register_render_object(mm);

	// 		mm->set_position({x * 2, scaled_height * 2, y * 2});
	// 	}
	// }

	// prinf("%d blocks created", app.current_scene()->render_objects().size());
/////////////////////////////////////////////////////////////////////////////////////////////////////
	// auto * m = mod_minecraft_block.create_instance();
	// FastNoiseLite noise;
	// noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	// nle::MultiMesh mm(mod_minecraft_block.mesh());

	// int size = 256;
	// for (int y = 0; y < size; y++)
	// {
	// 	for (int x = 0; x < size; x++)
	// 	{
	// 		int scaled_height = static_cast<int>((1.f + noise.GetNoise((float)x, (float)y)) * 10);
	// 		mm.create_mesh_instance({x*2, scaled_height *2, y*2});
			
	// 		// auto * mm = mod_minecraft_block.create_instance();
	// 		// app.current_scene()->add_child(mm);
	// 		// app.current_scene()->register_render_object(mm);

	// 		// mm->set_position({x * 2, scaled_height * 2, y * 2});
	// 	}
	// }

	// app.current_scene()->add_child(mm.create_instance());

	// prinf("%d blocks created", app.current_scene()->render_objects().size());

	app.run();

	return (0);
}
