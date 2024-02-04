// if (instance->active_note_list->length <= instance->max_notes) {
            //     for (unsigned short j = 0; j < 12; j++) {
            //         if (available_notes[j].midi_note_number == keys[i].midi_note_number) {
            //             instance->active_note_list->notes[instance->active_note_list->length - 1] = available_notes[j];
            //             break;
            //         }
            //     }
            // }

            // unsigned short index_to_remove = 0;
            // bool should_remove = false;
            // for (unsigned short j; j < instance->active_note_list->length; j++) {
            //     if (available_notes[j].midi_note_number == keys[i].midi_note_number) {
            //         should_remove = true;
            //         index_to_remove = j;
            //         break;
            //     }
            // }
            // if (should_remove) {
            //     for (unsigned short j = index_to_remove; j < instance->active_note_list->length -1; j++) {
            //         instance->active_note_list->notes[j] = instance->active_note_list->notes[j+1];
            //     }
            // }