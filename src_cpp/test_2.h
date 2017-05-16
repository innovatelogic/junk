
#pragma once

namespace junk
{
    namespace cpp_test_code
    {
        void MyFunction(char *Text)
        {
            char *Start = Text;
            while (Start)
            {
                while (*Start == ' '){ // skip white spaces
                    Start++;
                }

                int i = 0;
                while ((Start[i] != 0) && (Start[i] != ' ')){ // count next world characters
                    i++; 
                }

                // I suppose we do not need unnecessary memory copy here
                // if we can not change DisplayText function
                // and needs null terminating string here
                // we can try to simulate this behaviour in existent array

                bool use_optimization = false;
                char last_char;
                if (strlen(Start) > i) // barrier if it not a string endl
                {
                    use_optimization = true;
                    last_char = *(Start + i);
                    *(Start + i) = 0;
                }

                DisplayText(Start);	// Display text is provided and can't be optimized.
                
                if (use_optimization){
                    *(Start + i) = last_char; // return back
                }

                Start += i;
            }
        }
    }
}