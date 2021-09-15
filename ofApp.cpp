#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto R = 100.f;
	auto u = 0.f;
	auto u_step = 10.f;
	auto v_step = 5.f;

	ofColor color;
	for (int i = 0; i < 36; i++) {

		auto r = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, 10, 45);
		float angle_z = (i * 5) * DEG_TO_RAD;
		auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
		color.setHsb(ofMap(i, 0, 36, 0, 255), 230, 255);
		for (auto v = 0; v < 360; v += v_step) {

			vector<glm::vec3> vertices{
				glm::vec4(this->make_point(R, r, u, v), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, u + u_step, v + v_step), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, u, v + v_step), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, u - u_step, v), 0) * rotation_z
			};

			this->face.addVertices(vertices);
			this->line.addVertices(vertices);

			for (int k = 0; k < vertices.size(); k++) {

				this->face.addColor(ofColor(color, 138));
				this->line.addColor(color);
			}

			auto index = this->face.getVertices().size() - 1; // 末尾の番地

			this->face.addIndex(index - 3); this->face.addIndex(index - 2); this->face.addIndex(index - 1);
			this->face.addIndex(index); this->face.addIndex(index - 3); this->face.addIndex(index - 1);

			this->line.addIndex(index - 3); this->line.addIndex(index - 2);
			this->line.addIndex(index); this->line.addIndex(index - 1);

			u += u_step;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();
	this->line.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}