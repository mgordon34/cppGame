#include "SpriteBatch.h"

#include <algorithm>

namespace MattEngine {

	SpriteBatch::SpriteBatch()
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init() {
		createVertexArray();
	}


	void SpriteBatch::begin(GlyphSortType sortType) {
		_sortType = sortType;
		for (int i = 0; i < _glyphs.size(); i++) {
			delete _glyphs[i];
		}
		_glyphs.clear();
		_renderBatches.clear();
	}

	void SpriteBatch::end() {
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, Color color) {
		Glyph *newGlyph = new Glyph;
		newGlyph->textureID = textureID;
		newGlyph->depth = depth;
		
		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch() {
		glBindVertexArray(_vaoID);

		for (int i = 0; i < _renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].textureID);
			glDrawArrays(GL_QUADS, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray() {
		if (!_vaoID) {
			glGenVertexArrays(1, &_vaoID);
		}
		glBindVertexArray(_vaoID);
		if (!_vboID) {
			glGenBuffers(1, &_vboID);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position Attribute Pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		//Color Attribute Pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		//UV Attribute Pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches() {
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 4);
		if (_glyphs.empty()) {
			return;
		}

		int currVertex = 0;
		int offset = 0;
		_renderBatches.emplace_back(offset, 4, _glyphs[0]->textureID);
		vertices[currVertex++] = _glyphs[0]->topLeft;
		vertices[currVertex++] = _glyphs[0]->bottomLeft;
		vertices[currVertex++] = _glyphs[0]->bottomRight;
		vertices[currVertex++] = _glyphs[0]->topRight;
		offset += 4;

		for (int currGlyph = 1; currGlyph < _glyphs.size(); currGlyph++) {
			if (_glyphs[currGlyph]->textureID != _glyphs[currGlyph - 1]->textureID) {
				_renderBatches.emplace_back(offset, 4, _glyphs[currGlyph]->textureID);
			}
			else {
				_renderBatches.back().numVertices += 4;
			}
			vertices[currVertex++] = _glyphs[currGlyph]->topLeft;
			vertices[currVertex++] = _glyphs[currGlyph]->bottomLeft;
			vertices[currVertex++] = _glyphs[currGlyph]->bottomRight;
			vertices[currVertex++] = _glyphs[currGlyph]->topRight;
			offset += 4;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::sortGlyphs() {
		switch (_sortType) {
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
				break;
			case GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
				break;
			case GlyphSortType::TEXTURE:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
				break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b) {
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b) {
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph *a, Glyph *b) {
		return (a->textureID < b->textureID);
	}
}