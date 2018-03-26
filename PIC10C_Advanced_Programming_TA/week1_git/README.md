# Week 1 - Version Control (git)

## Demo: step-by-step initializing your own git repository
```bash
mkdir a_repo
cd a_repo
echo "Hello world!" > a_file.txt
git init
git status #always, always, git status, git status, git status, ALL THE TIME
git commit -m "init" # -m: attach message 
git status
git add a_file.txt
echo "Oops" >> a_file.txt
echo "Boom boom" > another.txt
git status
git commit -m "a_file.txt" #why does this not work?
```

Explore ```git commit -am [message]```, ```git log```, ```git checkout [commit id]``` (*detached HEAD*?), ```git reset``` (HEAD, --hard, --soft), ```git rm```, ```git revert```, etc.

## GitHub, GitLab, BitBucket, ...
* ssh key
* ```git push```
* collaborating with others

## diff-tool
* meld

## GUI
* gitk
* fork
* Or pick [your own cup of tea](https://git-scm.com/download/gui/mac)

## Side Notes
* StackOverflow is your good friend. Google *literally* your question and there's probably already an answer. 
* Like my terminal? Check [this](https://gist.github.com/kevin-smets/8568070) out! 
* Like my editor? Google ```vim``` (you can later email me and ask for my ```.vimrc```)
* Like my notes? Google ```MarkDown``` or check [this](https://jbt.github.io/markdown-editor/#bVNBbtswELzzFVs4gO3GltpremqTpgkQA0WTnoICoUVSpC1yBXJlJyn69y4pw84hgAnJ5HBmd2Y1gdkPRzfDenndyR1GreawknGrcB/gu3KEUYhvMrkGhqTN0IHRkoaooXOJLoSAj3BJsTu/hxouveInISS500BWg3GdPkGsM3QCHv4xvLGISR8vynQqASPcPKzuMsdVlC3IoEBF7EEWbnCBb1kdy+0OpQJHGXydDxsMpAMlkHyeqfk0lLp+/7qDhPCCAzQyQLIZkQmTEOJ26iEgtIgKJME+OnKhZQLfM2mdcZ2OQPqZFpmlxYJhCfSabMYycUy6M5UQd4jbBZeb/fpQ/DKI+bGWcXy8CvGV28pdTFMh4cqV/gAX55/Z4aenp43cydRE15M4m5khNOQwzOZ/BcDZbKrcbjqvLPluNr0F6VmMt6rp/Iv4x4vvC/FgXQL+PWKAMfA/M0vUp4u6bh3ZYV016OvNmmp/8H6pS/zz3GKnCbisbcA9OAO3U45p/Slus6NUSt7n8rld8ZPTSTmNVazgCnFdMsvyj7krGFlHdRb3UTGmiPcRN7qhVGfcQb2eL8BE9LC3rrEiZ+dC6l2U2YIsw4anRdEozll+ewGXo/Kc/QjjTIhBjfS5xMlkAvc0GJNHWmUOL7e6EI0D/Xi0wNG7Nr05f/s+52jjaXZ7GRMPQ2G85JZWLsY3necufdmqgqZ6vJwblHtdWkkvXP/z0rrWdryIax1NKYzH7WqTjpwJDe15lr0MTjapwtiWvfqIrnU4SI30cDzJc8ufBw7UD1QmENYdNttU5DZpqbTpJOl3HVEybLGVrj7hRpX21fV9pkYDSpI82s1zY3ixIn+MSfwH) out!
