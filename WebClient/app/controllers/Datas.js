require('../models/Data');

var mongoose = require('mongoose');
var Data = mongoose.model('Data');

var _ = require('lodash');

var Datas = {
  getCpuHeatInfos: function(req, res) {
    Data.find({data: 'cpu-heat'}, '-_id value createAt', function(err, datas) {
      if (err) throw err;
      var cpuHeatDatas = [];
      for (var i = 0; i < datas.length; i++) {
        cpuHeatDatas.push([datas[i].createAt, datas[i].value]);
      }
      res.render('datas/index', {datas: JSON.stringify(cpuHeatDatas)});
    });
  },
  
  getCpuFreqInfos: function(req, res) {
    Data.find({data: 'cpu-freq'}, '-_id value createAt', function(err, datas) {
      if (err) throw err;
      var cpuFreqDatas = [];
      for (var i = 0; i < datas.length; i++) {
        cpuFreqDatas.push([datas[i].createAt, datas[i].value]);
      }
      res.render('datas/index', {datas: JSON.stringify(cpuFreqDatas)});
    });
  },
  
  getStorageInfos: function(req, res) {
    Data.find({data: 'storage'}, '-_id value createAt', function(err, datas) {
      if (err) throw err;
      var storageDatas = [];
      for (var i = 0; i < datas.length; i++) {
        storageDatas.push([datas[i].createAt, datas[i].value]);
      }
      res.render('datas/index', {datas: JSON.stringify(storageDatas)});
    });
  },
  
  addDatas: function(req, res) {
    var socket = req.params.socket;
    
    // Create an array with different informations from the socket string
    var socketArray = _.split(socket, ':');
    
    // Calculating the average CPUs' heat (cpusHeatAv)
    var cpusHeat = socketArray[0].match(/.{1,2}/g);
    var cpusHeatAc = Number(cpusHeat[0]) + Number(cpusHeat[1]) + Number(cpusHeat[2]) + Number(cpusHeat[3]);
    var cpusHeatAv = Number(cpusHeatAc) / 4;
    
    // Stock informations from the socket array
    var cpuFreq = socketArray[1];
    var storageUsed = socketArray[5];
    var lastUptime = socketArray[2] + ':' + socketArray[3] +':' + socketArray[4];
    
    // Create new entries
    var addCpuHeat = new Data({
      data: 'cpu-heat',
      value: cpusHeatAv
    });
    var addCpuFreq = new Data({
      data: 'cpu-freq',
      value: cpuFreq
    });
    var addStorage = new Data({
      data: 'storage',
      value: storageUsed
    });
    var addUptime = new Data({
      data: 'uptime',
      uptime: lastUptime
    });
    
    // Save entries
    addCpuHeat.save(function(err) {
      if(err) throw err;
      console.log('New cpu heat value added.')
    });
    addCpuFreq.save(function(err) {
      if(err) throw err;
      console.log('New cpu frequency value added.')
    });
    addStorage.save(function(err) {
      if(err) throw err;
      console.log('New storage value added.')
    });
    addUptime.save(function(err) {
      if(err) throw err;
      console.log('New uptime value added.')
    });
  }
};

module.exports = Datas;