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

	app.window()->input_handler()->key_pressed().bind_callback([&](const int& key){
		switch(key)
		{
			case GLFW_KEY_ESCAPE:
			app.window()->close();
			break;
			case GLFW_KEY_F:
			app.window()->set_fullscreen(!app.window()->fullscreen());
			break;
			case GLFW_KEY_LEFT_CONTROL:
			app.window()->set_cursor_visibility(!app.window()->cursor_visibility());
			break;
			case GLFW_KEY_DOWN:
			app.current_scene()->light()->set_diffuse_intensity(app.current_scene()->light()->diffuse_intensity()-0.1);
			prdbg("%f", app.current_scene()->light()->diffuse_intensity());
			break;
			case GLFW_KEY_UP:
			app.current_scene()->light()->set_diffuse_intensity(app.current_scene()->light()->diffuse_intensity()+0.1);
			prdbg("%f", app.current_scene()->light()->diffuse_intensity());
			break;
			case GLFW_KEY_LEFT:
			app.current_scene()->light()->set_ambient_intensity(app.current_scene()->light()->ambient_intensity()-0.1);
			prdbg("%f", app.current_scene()->light()->ambient_intensity());
			break;
			case GLFW_KEY_RIGHT:
			app.current_scene()->light()->set_ambient_intensity(app.current_scene()->light()->ambient_intensity()+0.1);
			prdbg("%f", app.current_scene()->light()->ambient_intensity());
			break;
		}
	});

	app.current_scene()->camera()->set_rotation({0.f, 90.f, 0.f});
	app.current_scene()->light()->set_position(glm::vec3(0.f, 50.f, 0.f));
	app.current_scene()->light()->set_rotation({1.f, 0.f, 0.f});
	app.current_scene()->light()->set_ambient_intensity(0.5f);
	app.current_scene()->light()->set_diffuse_intensity(1.0f);
	app.current_scene()->light()->set_enabled(true);

	nle::Material m(1.0f, 32);

	auto rla = app.renderer()->render_layer_attributes(nle::RenderLayer::_0);
	rla.render_distance = 1000;
	app.renderer()->set_render_layer_attributes(nle::RenderLayer::_0, rla);

	nle::Model mod_minecraft_block("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	nle::Model mod_hasan("models/hasan/hasan.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/hasan/hasan.jpg", "hasan"));
	nle::Model mod_camera("models/obj-camera/source/Obj_Camera.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/obj-camera/textures/Texture_OldCamera_copy.png", "camera"));
	// nle::Model mod_ambulance("models/2203/source/raf_ambulance/raf-22031.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/2203/textures/raf_22031_tex_d.png", "ambulance"));

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	int size = 20;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int scaled_height = static_cast<int>((1.f + noise.GetNoise((float)x, (float)y)) * 10);
			auto * mm = mod_minecraft_block.create_instance();
			mm->set_material_for_meshes(&m);
			app.current_scene()->add_child(mm);

			mm->set_position({x * 2, scaled_height * 2, y * 2});
		}
	}

	prinf("%d blocks created", app.current_scene()->render_objects().size());
	
	auto *h = mod_camera.create_instance();
	// h->set_material_for_meshes(&m);
	h->set_position(app.current_scene()->light()->position());
	app.current_scene()->add_child(h);

	app.run();

	return (0);
}
