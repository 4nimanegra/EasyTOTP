if [ "$SSH_CONNECTION" != "" ]; then

	if [ "$SSH_ORIGINAL_COMMAND" == "" ]; then

		SSH_ORIGINAL_COMMAND=/bin/bash;

	fi;

	AUX=`echo $SSH_ORIGINAL_COMMAND | cut -f "1" -d " "`;

	if [ "$AUX" != "scp" ]; then

		~/totp ~/mysecretotpfile.txt;

		if [ $? == 0 ]; then

			$SSH_ORIGINAL_COMMAND;

		fi;

	else

		if [ -e ~/scpenable ]; then

			$SSH_ORIGINAL_COMMAND;
			rm ~/scpenable;
	
		fi;
	fi;
fi;
