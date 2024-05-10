sudo setpci -s 3b:00.1 68.w=393e
IRQBALANCE_BANNED_CPUS=0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46 irqbalance --oneshot
systemctl stop irqbalance
sudo sysctl -w vm.swappiness=0
sudo sysctl -w vm.zone_reclaim_mode=0
sudo ethtool -A ens1f1np1 rx off tx off
sudo ethtool -A ens1f0np0 rx off tx off
