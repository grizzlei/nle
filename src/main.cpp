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

	nle::MultiMeshInstance *hasan;

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
			case GLFW_KEY_G:
			app.renderer()->gui()->set_visible(!app.renderer()->gui()->visible());
			break;
			case GLFW_KEY_Z:
			// app.renderer()->gui()->set_visible(!app.renderer()->gui()->visible());
			app.current_scene()->light()->set_position(app.current_scene()->light()->position() - glm::vec3(1.0, 0.f, 0.f));
	hasan->set_position(app.current_scene()->light()->position());
			break;
			case GLFW_KEY_X:
			app.current_scene()->light()->set_position(app.current_scene()->light()->position() + glm::vec3(1.0, 0.f, 0.f));
	hasan->set_position(app.current_scene()->light()->position());
			break;
			case GLFW_KEY_C:
			app.current_scene()->light()->set_position(app.current_scene()->light()->position() - glm::vec3(0.0, 1.f, 0.f));
	hasan->set_position(app.current_scene()->light()->position());
			break;
			case GLFW_KEY_V:
			app.current_scene()->light()->set_position(app.current_scene()->light()->position() + glm::vec3(0.0, 1.f, 0.f));
	hasan->set_position(app.current_scene()->light()->position());
			break;
			case GLFW_KEY_B:
			app.current_scene()->light()->set_rotation(app.current_scene()->light()->rotation() - glm::vec3(0.0, 1.f, 0.f));
	hasan->set_rotation(app.current_scene()->light()->rotation());
			break;
			case GLFW_KEY_N:
			app.current_scene()->light()->set_rotation(app.current_scene()->light()->rotation() + glm::vec3(0.0, 1.f, 0.f));
	hasan->set_rotation(app.current_scene()->light()->rotation());
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

	app.renderer()->gui()->set_draw_callback([&](){
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Load Model"))
                {
                    prdbg("Load Model");
                }
                if(ImGui::MenuItem("Quit"))
                {
					app.window()->close();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if(ImGui::Begin("nice little engine", nullptr, ImGuiWindowFlags_MenuBar))
        {
            ImGui::TextWrapped("https://github.com/grizzlei/nle");
            ImGui::TextWrapped("hasan karaman - 2023");
            ImGui::TextWrapped("experimental opengl renderer");
            ImGui::Separator();

			glm::vec3 v3val;
			float fval;
			bool bval;

			// light settings
			ImGui::TextWrapped("light settings:");
			fval = app.current_scene()->light()->ambient_intensity();
			ImGui::SliderFloat("ambient intensity", &fval, 0.f, 1.f);
			app.current_scene()->light()->set_ambient_intensity(fval);

			fval = app.current_scene()->light()->diffuse_intensity();
			ImGui::SliderFloat("diffuse intensity", &fval, 0.f, 1.f);
			app.current_scene()->light()->set_diffuse_intensity(fval);
			
			// camera settings
			ImGui::TextWrapped("camera settings:");
			ImGui::TextWrapped("position:");
			v3val = app.current_scene()->camera()->position();
			ImGui::SetNextItemWidth(60.f);
			ImGui::InputFloat("x", &v3val.x);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(60.f);
			ImGui::InputFloat("y", &v3val.y);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(60.f);
			ImGui::InputFloat("z", &v3val.z);
			app.current_scene()->camera()->set_position(v3val);

			bval = app.window()->fullscreen();
			ImGui::Checkbox("fullscreen", &bval);
			app.window()->set_fullscreen(bval);

			for(auto * i : app.current_scene()->children())
			{
				nle::MultiMeshInstance *mi = dynamic_cast<nle::MultiMeshInstance*>(i);
				if(mi)
				{
					ImGui::Text("%s", mi->id().c_str());
					if(ImGui::Button(i->id().c_str()))
					{
						mi->set_render_mode(mi->render_mode() == nle::Fill ? nle::Point : nle::Fill);
					}
				}
			}
            
            ImGui::End();
        }
	});

	nle::Material material(4.0f, 32);

	auto rla = app.renderer()->render_layer_attributes(nle::RenderLayer::_0);
	rla.render_distance = 1000;
	app.renderer()->set_render_layer_attributes(nle::RenderLayer::_0, rla);

	nle::Model mod_minecraft_block("models/Minecraft_Grass_Block_OBJ/Grass_Block.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", "grass_block"));
	nle::Model mod_hasan("models/hasan/hasan.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/hasan/hasan.jpg", "hasan"));
	nle::Model mod_camera("models/obj-camera/source/Obj_Camera.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/obj-camera/textures/Texture_OldCamera_copy.png", "camera"));
	nle::Model mod_car("models/1re1lk582a3k-house/house.obj", nle::DEFAULT_SHADER);
	// nle::Model mod_car("models/85-cottage_obj/cottage_obj.obj", nle::DEFAULT_SHADER, app.texture_factory()->load_and_get("models/85-cottage_obj/cottage_textures/cottage_diffuse.png", "cottage"));

	prdbg("%d blocks created", app.current_scene()->render_objects().size());

	hasan = mod_hasan.create_instance();
	hasan->set_scale(glm::vec3(10.f));
	app.current_scene()->add_child(hasan);
	hasan->set_position(app.current_scene()->light()->position());

	auto *house = mod_car.create_instance();
	house->set_material_for_meshes(&material);
	app.current_scene()->add_child(house);

	app.run();
	prdbg("%s", app.current_scene()->to_json().dump().c_str());

	return (0);
}
