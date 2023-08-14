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
			app.current_scene()->camera()->set_free_roam(!app.current_scene()->camera()->free_roam());
			app.window()->set_cursor_visibility(!app.current_scene()->camera()->free_roam());
			break;
			case GLFW_KEY_DOWN:
			// app.current_scene()->light()->set_diffuse_intensity(app.current_scene()->light()->diffuse_intensity()-0.1);
			app.current_scene()->camera()->set_rotation(app.current_scene()->camera()->rotation()-glm::vec3(1.f, 0.f, 0.f));
			prdbg("%f", app.current_scene()->light()->diffuse_intensity());
			break;
			case GLFW_KEY_UP:
			// app.current_scene()->light()->set_diffuse_intensity(app.current_scene()->light()->diffuse_intensity()+0.1);
			app.current_scene()->camera()->set_rotation(app.current_scene()->camera()->rotation()+glm::vec3(1.f, 0.f, 0.f));
			prdbg("%f", app.current_scene()->light()->diffuse_intensity());
			break;
			case GLFW_KEY_LEFT:
			app.current_scene()->camera()->set_rotation(app.current_scene()->camera()->rotation()-glm::vec3(0.f, 1.f, 0.f));
			// app.current_scene()->light()->set_ambient_intensity(app.current_scene()->light()->ambient_intensity()-0.1);
			prdbg("%f", app.current_scene()->light()->ambient_intensity());
			break;
			case GLFW_KEY_RIGHT:
			app.current_scene()->camera()->set_rotation(app.current_scene()->camera()->rotation()+glm::vec3(0.f, 1.f, 0.f));
			// app.current_scene()->light()->set_ambient_intensity(app.current_scene()->light()->ambient_intensity()+0.1);
			prdbg("%f", app.current_scene()->light()->ambient_intensity());
			break;
			case GLFW_KEY_G:
			app.renderer()->gui()->set_visible(!app.renderer()->gui()->visible());
			break;
		}
	});

	app.current_scene()->set_id("scene_root");
	app.current_scene()->camera()->set_rotation({-15.f, 0.f, 0.f});
	app.current_scene()->camera()->set_position({-50.f, 50.f, -50.f});
	app.current_scene()->light()->set_position(glm::vec3(0.f, 100.f, 0.f));
	app.current_scene()->light()->set_rotation({180.f, 0.f, 0.f});
	app.current_scene()->light()->set_ambient_intensity(0.5f);
	app.current_scene()->light()->set_diffuse_intensity(1.0f);
	app.current_scene()->light()->set_enabled(true);

	nle::Material material(4.0f, 32);

	auto rla = app.renderer()->render_layer_attributes(nle::RenderLayer::_0);
	rla.render_distance = 1000;
	app.renderer()->set_render_layer_attributes(nle::RenderLayer::_0, rla);

	nle::Model mod_minecraft_block("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	nle::Model mod_hasan("models/hasan/hasan.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/hasan/hasan.jpg", "hasan"));
	nle::Model mod_camera("models/obj-camera/source/Obj_Camera.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/obj-camera/textures/Texture_OldCamera_copy.png", "camera"));
	nle::Model mod_car("models/OBJ/NormalCar1.obj", nle::DEFAULT_SHADER);

	prdbg("%d blocks created", app.current_scene()->render_objects().size());

	auto *car = mod_car.create_instance();
	app.current_scene()->add_child(car);

	app.run();
	prdbg("%s", app.current_scene()->to_json().dump().c_str());

	return (0);
}
