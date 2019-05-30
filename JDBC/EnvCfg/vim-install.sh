mkdir ~/pkg
cd ~/pkg
git clone https://github.com/vim/vim.git
cp -r vim vim_bak
cd vim/src

sudo apt-get install libncurses5-dev python-dev python3-dev libbonoboui2-dev libcairo2-dev \
libx11-dev libxpm-dev libxt-dev

./configure --with-features=huge --enable-multibyte --enable-rubyinterp --enable-pythoninterp --enable-python3interp \
--enable-luainterp --enable-cscope  --enable-perlinterp --with-python-config-dir=/usr/lib/python2.7/config-x86_64-linux-gnu/ \
--with-python3-config-dir=/usr/lib/python3.5/config-3.5m-x86_64-linux-gnu/ --prefix=/usr/local/vim

sudo apt-get remove vim vim-runtime vim-tiny vim-common
make
sudo make install