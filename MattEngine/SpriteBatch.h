#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "vertex.h"

namespace MattEngine {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {
		GLuint textureID;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex bottomRight;
		Vertex topRight;
	};

	class RenderBatch {
	public:
		RenderBatch(GLuint offset, GLuint numVertices, GLuint textureID) : 
			offset(offset), numVertices(numVertices), textureID(textureID) {

		};

		GLuint offset;
		GLuint numVertices;
		GLuint textureID;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, Color color);

		void renderBatch();

	private:
		GLuint _vboID;
		GLuint _vaoID;

		std::vector<Glyph *> _glyphs;
		std::vector<RenderBatch> _renderBatches;
		GlyphSortType _sortType;

		void createVertexArray();
		void createRenderBatches();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph *a, Glyph *b);
		static bool compareBackToFront(Glyph *a, Glyph *b);
		static bool compareTexture(Glyph *a, Glyph *b);
	};

}