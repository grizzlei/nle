#include "nle/Window.h"
#include "nle/Scene.h"
#include "nle/Renderer3D.h"
#include "nle/Texture.h"
#include "nle/Mesh.h"
#include "nle/ModelObj.h"
#include "nle/Nle.h"

#include <glm/gtc/random.hpp>

#include "FastNoiseLite.h"

int main(int argc, char *argv[])
{
	nle::Nle app;

	app.currentScene()->camera()->setPosition({0.f, 200.f, -200.f});
	app.currentScene()->camera()->setRotation({0.f, 90.f, 0.f});
	app.currentScene()->light()->setAmbientIntensity(.05f);
	app.currentScene()->light()->setDiffuseIntensity(1.f);
	app.currentScene()->light()->setRotation(glm::vec3(2.f, -1.f, -2.f));
	app.currentScene()->light()->setEnabled(true);

	app.textureFactory()->load("models/hasan/hasan.jpg", "hasan");
	app.physicsEngine()->attachPhysicsCallback([&](nle::Object3D *o, double delta){
		nle::Scene * s = dynamic_cast<nle::Scene*>(o->root());
		if(s)
		{
			prdbg("delta: %f", delta);
		}
	});
	
	nle::ModelOBJ modHasan(nle::DEFAULT_SHADER, app.textureFactory()->get("hasan"));
	if(modHasan.load("models/hasan/hasan.obj"))
	{
		for(int i = 0; i < 10; i++)
		{
			auto rnd = glm::sphericalRand(200.f);
			nle::MultiMeshInstance *mm = modHasan.createInstance();
			mm->setPosition(rnd + glm::vec3(0.f, 1000.f, 0.f));
			mm->setScale(glm::vec3(50.f));
			app.currentScene()->addChild(mm);
			app.physicsEngine()->attachPhysicsBody(mm);
		}
	}

	auto thrAmbient = std::thread([&](){
		float intensity = 0.f;
		float step = 0.001f;
		int direction = 1;

		while(!app.window()->closed())
		{
			for(int j = 0; (j < 1000) && !app.window()->closed(); j++)
			{
				app.currentScene()->light()->setAmbientIntensity(intensity);
				intensity += (step * direction);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			direction *= -1;
		}
	});

	app.run();
	if(thrAmbient.joinable())
	{
		thrAmbient.join();
	}

	return (0);
}
