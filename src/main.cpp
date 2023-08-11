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

	app.current_scene()->camera()->set_rotation({0.f, 90.f, 0.f});
	app.current_scene()->light()->set_ambient_intensity(1.0f);
	app.current_scene()->light()->set_diffuse_intensity(1.f);
	app.current_scene()->light()->set_rotation(glm::vec3(2.f, -1.f, -2.f));
	app.current_scene()->light()->set_enabled(true);

	auto rla = app.renderer()->render_layer_attributes(nle::RenderLayer::_0);
	rla.render_distance = 1000;
	app.renderer()->set_render_layer_attributes(nle::RenderLayer::_0, rla);

	nle::Model mod_minecraft_block("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	nle::Model mod_hasan("models/hasan/hasan.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/hasan/hasan.jpg", "hasan"));
	
	auto *mmi = mod_hasan.create_instance();
	mmi->set_scale(glm::vec3(100.f));

	app.current_scene()->add_child(mmi);
	app.current_scene()->register_render_object(mmi);

	app.run();

	return (0);
}
