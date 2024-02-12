#include "sentencepiece_processor.h"
#include <vector>

extern "C" {

  void * spm_new_sentencepiece_processor()
  {
    return (void*) new sentencepiece::SentencePieceProcessor();
  }

  bool spm_load_model(void * ptr_inst, char * model_file)
  {
    sentencepiece::SentencePieceProcessor * instance = (sentencepiece::SentencePieceProcessor*) ptr_inst;
    auto status = instance->Load(model_file);
    return status.ok();
  }

  int spm_get_piece_size(void * ptr_inst)
  {
    sentencepiece::SentencePieceProcessor * instance = (sentencepiece::SentencePieceProcessor*) ptr_inst;
    return instance->GetPieceSize();
  }
  
  int spm_encode(void * ptr_inst, char* text, int * buffer, int buffer_length)
  {
    sentencepiece::SentencePieceProcessor * instance = (sentencepiece::SentencePieceProcessor*) ptr_inst;
    std::vector<int> ids;
    auto status = instance->Encode(text, &ids);
    if(!status.ok())
      return -1 * (int)status.code();
    auto count=0;
    for(auto it=ids.begin(); count<buffer_length && it != ids.end(); ++it, ++buffer, ++count) {
      *buffer = *it;
    }
    return ids.size();
  }

  int spm_piece_to_id(void * ptr_inst, char* token)
  {
    sentencepiece::SentencePieceProcessor * instance = (sentencepiece::SentencePieceProcessor*) ptr_inst;
    return instance->PieceToId(token);
  }  
}
