Vagrant.configure(2) do |config|
  config.vm.box = "bento/ubuntu-12.04"
  config.vm.network "forwarded_port", guest: 80, host: 8000
  config.vm.synced_folder "src/", "/home/vagrant/src"

  config.vm.provision :chef_solo do |chef|
    chef.cookbooks_path = %w[cookbooks]
    chef.add_recipe 'development'
  end
end
