pipeline {

    agent any

    stages {

        stage("build") {
            steps {
                echo "building the app..."
                sh 'cmake .'
                sh 'make'
            }
        }

        stage("deploy") {
            steps {
                echo "deploying the app..."
                sh './DirAnalyzer'
                echo ":)"
            }
        }

    }

}