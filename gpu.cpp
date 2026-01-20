/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <studentSolution/gpu.hpp>

void student_GPU_run(GPUMemory&mem,CommandBuffer const&cb);

void processCommands(GPUMemory&mem,CommandBuffer const&cb);

void clearColor(GPUMemory&mem,ClearColorCommand cmd);

void clearDepth(GPUMemory&mem,ClearDepthCommand cmd);

void clearStencil(GPUMemory&mem,ClearStencilCommand cmd);

void draw(GPUMemory&mem, DrawCommand const&cmd);

uint32_t getIndex(GPUMemory const&mem,uint32_t i);

void assembleInVertex(InVertex&inVertex, GPUMemory const&mem, uint32_t vertexID);




void student_GPU_run(GPUMemory&mem,CommandBuffer const&cb){
  mem.gl_DrawID = 0; //reset counteru pre pocet kresleni
  processCommands(mem, cb);
  
}

// ColorBuffer cleaning
void clearColor(GPUMemory&mem,ClearColorCommand cmd){
  Framebuffer*fbo = mem.framebuffers + mem.activatedFramebuffer;
  
  if(fbo->color.data){
    for(uint32_t y=0;y<fbo->height;++y)
      for(uint32_t x=0;x<fbo->width;++x){
        void*pixelStart = getPixel(fbo->color,x,y);  // starter (pozicia)

        for(uint32_t i=0;i<fbo->color.channels;++i){ // pre kazdy channel setneme hodnotu
          if(fbo->color.format == Image::F32){  // pre float
            ((float*)pixelStart)[i] = cmd.value[i];
          }
          else if(fbo->color.format == Image::U8){ // pre unsigned int
            ((uint8_t*)pixelStart)[i] = (uint8_t)(cmd.value[i]*255.f);
          }
        }
      }
  }
}

void clearDepth(GPUMemory&mem,ClearDepthCommand cmd){
  Framebuffer*fbo = mem.framebuffers + mem.activatedFramebuffer;
 
  if(fbo->depth.data){
    for(uint32_t y=0;y<fbo->height;++y)
      for(uint32_t x=0;x<fbo->width;++x){
        void*pixelStart = getPixel(fbo->depth,x,y);

        if(fbo->depth.format == Image::F32){
          *((float*)pixelStart) = cmd.value;
        }
        else if(fbo->depth.format == Image::U8){
          *((uint8_t*)pixelStart) = (uint8_t)(cmd.value * 255.f);
        }
      }
  }
}


void clearStencil(GPUMemory&mem,ClearStencilCommand cmd){
  Framebuffer*fbo = mem.framebuffers + mem.activatedFramebuffer;
 
  if(fbo->stencil.data){
    for(uint32_t y=0;y<fbo->height;++y)
    for(uint32_t x=0;x<fbo->width;++x){
      void*pixelStart = getPixel(fbo->stencil,x,y);

      if(fbo->stencil.format == Image::F32){
        *((float*)pixelStart) = (float)(cmd.value);
      }
      else if(fbo->stencil.format == Image::U8){
        *((uint8_t*)pixelStart) = cmd.value;
      }
    }
  }
}

void processCommands(GPUMemory& mem, CommandBuffer const& cb) {
  for (uint32_t i = 0; i < cb.nofCommands; ++i) {
    CommandType type = cb.commands[i].type;
    CommandData data = cb.commands[i].data;

    switch (type) {
      //test 0
      case CommandType::BIND_FRAMEBUFFER:
        mem.activatedFramebuffer = data.bindFramebufferCommand.id;
        break;
      //test 1
      case CommandType::BIND_PROGRAM:
        mem.activatedProgram = data.bindProgramCommand.id;
        break;
      //test 2
      case CommandType::BIND_VERTEXARRAY:
        mem.activatedVertexArray = data.bindVertexArrayCommand.id;
        break;
      //test 3
      case CommandType::BLOCK_WRITES_COMMAND:
        mem.blockWrites = data.blockWritesCommand.blockWrites;
        break;
      //test 4
      case CommandType::SET_BACKFACE_CULLING_COMMAND:
        mem.backfaceCulling.enabled = data.setBackfaceCullingCommand.enabled;
        break;
      //test 5
      case CommandType::SET_FRONT_FACE_COMMAND:
        mem.backfaceCulling.frontFaceIsCounterClockWise = data.setFrontFaceCommand.frontFaceIsCounterClockWise;
        break;
      //test 6
      case CommandType::SET_STENCIL_COMMAND:
        mem.stencilSettings = data.setStencilCommand.settings;
        break;
      //test 7
      case CommandType::DRAW:
        draw(mem, data.drawCommand);
        mem.gl_DrawID++;
        break;
      //test 8
      case CommandType::SET_DRAW_ID:
        mem.gl_DrawID = data.setDrawIdCommand.id;
        break;
      //test 9
      case CommandType::CLEAR_COLOR:
        clearColor(mem, data.clearColorCommand);
        break;
      //test 10
      case CommandType::CLEAR_DEPTH:
        clearDepth(mem, data.clearDepthCommand);
        break;
      //test 11
      case CommandType::CLEAR_STENCIL:
        clearStencil(mem, data.clearStencilCommand);
        break;
      //test 12
      case CommandType::USER_COMMAND:
        if (data.userCommand.callback) {
          data.userCommand.callback(data.userCommand.data);
        }
        break;
      //test 13
      case CommandType::SUB_COMMAND:
        if (data.subCommand.commandBuffer) {
          processCommands(mem, *data.subCommand.commandBuffer);
        }
        break;
    }
  }
}

// Funkcia zisti index vertex index.
// Ak je puzity indexbuffer returne ho z bufferu
// inak returne i
// (teda indexovane a neindexovane kreslenie)
uint32_t getIndex(GPUMemory const&mem,uint32_t i){
  auto const&vao = mem.vertexArrays[mem.activatedVertexArray]; //aktualny vertex array

  if(vao.indexBufferID >= 0){ // INDEXOVANE kreslenie
    Buffer indexBuffer = mem.buffers[vao.indexBufferID]; // indexbuffer
    const uint8_t*ptr = (const uint8_t*)indexBuffer.data + vao.indexOffset; // head na data v indexbuffery
    
    switch (vao.indexType){  // 8bit/16bit/32bit
      case IndexType::U8:
        return ((const uint8_t*)ptr)[i];
      case IndexType::U16:
        return ((const uint16_t*)ptr)[i];
      case IndexType::U32:
        return ((const uint32_t*)ptr)[i];
      default:
        return i;
    }
  }
  else {  // NEINDEXOVANE kreslenie
    return i;
  }
}

// Attributy pre InVertexy
void assembleInVertex(InVertex&inVertex, GPUMemory const&mem, uint32_t vertexID) {
  inVertex.gl_VertexID = vertexID;  // setneme ID vertexu

  auto const& vao = mem.vertexArrays[mem.activatedVertexArray]; //aktualny vertex

  for (uint32_t j = 0; j < maxAttribs; ++j) { //loop cez vsetky atributy
    auto const& attrib = vao.vertexAttrib[j];

    if (attrib.type == AttribType::EMPTY) continue; // prazdny alebo bez platneho
    if (attrib.bufferID < 0) continue;              // bufferu skipneme

    Buffer const& buffer = mem.buffers[attrib.bufferID]; // buffer daneho atributu
    
    const uint8_t* data = (const uint8_t*)buffer.data;  // head na data bufferu
    const uint8_t* ptr = data + attrib.offset + attrib.stride * vertexID; // adresa (offset dat)

    switch (attrib.type) { // typy atributov
      case AttribType::FLOAT:
        inVertex.attributes[j].v1 = *(float*)(ptr);
        break;
      case AttribType::VEC2:
        inVertex.attributes[j].v2 = *(glm::vec2*)(ptr);
        break;
      case AttribType::VEC3:
        inVertex.attributes[j].v3 = *(glm::vec3*)(ptr);
        break;
      case AttribType::VEC4:
        inVertex.attributes[j].v4 = *(glm::vec4*)(ptr);
        break;
      case AttribType::UINT:
        inVertex.attributes[j].u1 = *(uint32_t*)(ptr);
        break;
      default:
        break;
    }
  }
}


// Kreslenie podla DrawCommandu
void draw(GPUMemory&mem, DrawCommand const&cmd) {
  Program &program = mem.programs[mem.activatedProgram]; //aktualny program
  
  VertexShader vs = program.vertexShader; //aktualny vertex shader
  if(vs == nullptr) return; //test ci existuje
  
  auto const& vao = mem.vertexArrays[mem.activatedVertexArray]; //aktualny vertex Array
  
  for (uint32_t i = 0; i < cmd.nofVertices; ++i) {
    InVertex inVertex;    //input vertex shader
    OutVertex outVertex;  //output vertex shader
    ShaderInterface si;
    
    inVertex.gl_VertexID = getIndex(mem, i); // index vrcholu
    assembleInVertex(inVertex, mem, inVertex.gl_VertexID);
    
    
    si.uniforms = mem.uniforms;   // uniformy shaderu
    si.textures = mem.textures;   // textury shaderu
    si.gl_DrawID = mem.gl_DrawID; // ID kreslenia
    
    // call vertex shader
    vs(outVertex, inVertex, si);
  }
}




