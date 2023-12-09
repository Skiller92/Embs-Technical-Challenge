import 'package:flutter/material.dart';
import 'package:fl_chart/fl_chart.dart';

class ChartPage extends StatelessWidget {
  final Stream<HealthData> healthDataStream;
  final Stream<EnvironmentData> environmentDataStream;

  ChartPage({required this.healthDataStream, required this.environmentDataStream});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Health Data'),
      ),
      body: StreamBuilder(
        stream: healthDataStream,
        builder: (context, snapshot) {
          if (!snapshot.hasData) {
            return Center(child: CircularProgressIndicator());
          }

          HealthData healthData = snapshot.data as HealthData;

          return Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Text('Glucose Level: ${healthData.glucoseLevel}'),
              Text('Heart Rate: ${healthData.heartRate}'),
              Text('Blood Pressure: ${healthData.bloodPressure}'),
              LineChart(
                // Implement the chart based on your requirements
                // Check fl_chart documentation for customization
                // Example: https://github.com/imaNNeoFighT/fl_chart
              ),
            ],
          );
        },
      ),
    );
  }
}

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final FirebaseService firebaseService = FirebaseService();

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: DefaultTabController(
        length: 2,
        child: Scaffold(
          appBar: AppBar(
            title: Text('Health Monitoring App'),
            bottom: TabBar(
              tabs: [
                Tab(text: 'Health Data'),
                Tab(text: 'Environment Data'),
              ],
            ),
          ),
          body: TabBarView(
            children: [
              ChartPage(healthDataStream: firebaseService.getHealthDataStream(), environmentDataStream: null),
              ChartPage(healthDataStream: null, environmentDataStream: firebaseService.getEnvironmentDataStream()),
            ],
          ),
        ),
      ),
    );
  }
}
